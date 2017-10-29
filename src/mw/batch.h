#ifndef BATCH_H
#define BATCH_H

#include <mw/vertexarrayobject.h>
#include <mw/vertexbufferobject.h>
#include <mw/buffer.h>
#include <mw/texture.h>
#include <mw/window.h>

#include <iostream>
#include <algorithm>
#include <vector>

namespace mw {

	template <class Shader>
	class Batch : public mw::VertexArrayObject {
	public:
		using iterator = typename std::vector<typename Shader::Vertex>::iterator;
		using const_iterator = typename std::vector<typename Shader::Vertex>::const_iterator;

		Batch(GLenum mode, GLenum usage, const std::shared_ptr<Shader>& shader, unsigned int maxVertexes) :
			mode_(mode), usage_(usage), index_(0),
			uploadedIndex_(0), shader_(shader), data_(maxVertexes) {

			if (usage == GL_STATIC_DRAW) {
				data_.clear();
			}
		}

		Batch(GLenum mode, const std::shared_ptr<Shader>& shader) :
			mode_(mode), usage_(GL_STATIC_DRAW), index_(0),
			uploadedIndex_(0), shader_(shader) {
		}

		virtual ~Batch() = default;

		Batch(const Batch& batch) = delete;
		Batch &operator=(const Batch& batch) = delete;

		GLenum getMode() const {
			return mode_;
		}

		GLenum getUsage() const {
			return usage_;
		}

		int getMaxVertexes() const {
			return data_.size();
		}

		int getUploadedVertexes() const {
			return maxVertexes;
		}

		float getVboSizeInMiB() const {
			return sizeof(Shader::Vertex) * data_.size() * 1.f / 1024 / 1024;
		}

		void useProgram() const override {
			shader_->useProgram();
		}

		void setVertexAttribPointer() const override {
			shader_->setVertexAttribPointer();
		}

		void bindBuffer() const override {
			vbo_.bindBuffer();
		}

		void clear() {
			index_ = 0;
			if (usage_ != GL_STATIC_DRAW) {
				// Can only clear data if the vbo is not updated. 
				uploadedIndex_ = 0;
			}
		}

		void getSize() const {
			return index_;
		}

		iterator begin() {
			return data_.begin();
		}

		iterator end() {
			return data_.end();
		}

		const_iterator begin() const {
			return data_.begin();
		}

		const_iterator end() const {
			return data_.end();
		}

		void uploadToGraphicCard() {
			if (mw::Window::getOpenGlMajorVersion() >= 2) {
				if (vbo_.getSize() > 0) {
					if (usage_ != GL_STATIC_DRAW) {
						vbo_.bindBufferSubData(0, index_ * sizeof(Shader::Vertex), data_.data());
						uploadedIndex_ = index_;
					}
				} else {
					if (usage_ == GL_STATIC_DRAW) {
						vbo_.bindBufferData(GL_ARRAY_BUFFER, index_ * sizeof(Shader::Vertex), data_.data(), usage_);
					} else {
						vbo_.bindBufferData(GL_ARRAY_BUFFER, data_.size() * sizeof(Shader::Vertex), data_.data(), usage_);
					}
					uploadedIndex_ = index_;
				}
			}
		}

		virtual void draw() const {
			if (vbo_.getSize() > 0) {
				if (uploadedIndex_ > 0) { // Data is avaiable to be drawn.
					useProgram();
					bind();
					glDrawArrays(mode_, 0, index_);
					mw::checkGlError();
				}
			} else {
				std::cerr << "VertexData failed to draw, no vbo binded, i.e. Batch::uploadToGraphicCard never called." << std::endl;
			}
		}

		void add(typename const Shader::Vertex& v) {
			if (usage_ != GL_STATIC_DRAW) {
				data_[index_++] = v;
			} else {
				if (vbo_.getSize() == 0) {
					data_.push_back(v);
					++index_;
				} else {
					std::cerr << "VertexData is static, data can't be modified." << std::endl;
				}
			}
		}

		template<class InputIterator>
		void add(InputIterator begin, InputIterator end) {
			if (usage_ != GL_STATIC_DRAW) {
				std::copy(begin, end, data_.begin() + index_);
				index_ += end - begin;
			} else {
				if (vbo_.getSize() == 0) {
					// Only add data before the vbo is created.
					std::copy(begin, end, data_.begin() + index_);
					index_ += end - begin;
				} else {
					std::cerr << "VertexData is static, data can't be modified." << std::endl;
				}
			}

			data_.insert(data_.end(), begin, begin);
		}

		void add(const std::vector<typename Shader::Vertex>& data) {
			add(data.begin(), data.end());
		}

	private:
		const GLenum usage_;
		const GLenum mode_;
		unsigned int index_;
		unsigned int uploadedIndex_;
		std::vector<typename Shader::Vertex> data_;
		std::shared_ptr<Shader> shader_;
		mw::VertexBufferObject vbo_;
	};

} // Namespace mw.

#endif // BATCH_H
