template<typename T>
class Tensor {
public:
    Tensor () {
        shape_ = std::vector<size_t> {0,0,0};
        data_ = std::vector<T> ();
    }
    Tensor(std::vector<size_t> shape) : shape_(shape), data_(shape[0]*shape[1]*shape[2], T()) {
    }
    Tensor(const Tensor& tensr) : shape_(tensr.getsize()), data_(shape_[0]*shape_[1]*shape_[2], T()) {
        *this = tensr;
    }

    T& operator()(size_t i, size_t j, size_t k) {
        return data_[i* shape_[1] + j + k * shape_[0] * shape_[1]];
    }

    const T& operator()(size_t i, size_t j, size_t k) const {
        return data_[i * shape_[1] + j + k * shape_[0] * shape_[1]];
    }

    Tensor dot(const Tensor& mat) const {
        // assert()
        Tensor temp(std::vector<size_t> {this->shape_[0], mat.shape_[1], this->shape_[2]});
        for(size_t i= 0;i<this->shape_[0];++i) {
            for(size_t j=0;j<mat.shape_[1];++j) {
                float sum=0;
                for(size_t k=0;k<mat.shape_[0];++k) {
                    sum += (*this)(i,k,0) * mat(k,j,0);
                }
                temp(i,j,0) = sum;
            }
        }
        return temp;
    }

    Tensor transpose() const {
        Tensor temp(std::vector<size_t> {this->shape_[1],this->shape_[0],this->shape_[2]});
        for(size_t k=0;k<this->shape_[2];++k) {
            for(size_t i=0;i<this->shape_[1];++i) {
                for(size_t j=0;j<this->shape_[0];++j)
                    temp(i,j,k) = (*this)(j,i,k);
            }
        }

        return temp;
    }
    
    Tensor sum() const{
        Tensor temp(std::vector<size_t> {this->shape_[0],1,this->shape_[2]});
        for(size_t k=0;k<this->shape_[2];++k) {
            for(size_t i=0;i<this->shape_[0];++i) {
                for(size_t j=0;j<this->shape_[1];++j)
                    temp(i,0,k) = temp(i,0,k) + (*this)(i,j,k);
            }
        }

        return temp;
    }

    void fill(const float& num) {
        for(size_t k=0;k<this->shape_[2];++k) {
            for(size_t i=0;i<this->shape_[1];++i) {
                for(size_t j=0;j<this->shape_[0];++j)
                    (*this)(i,j,k) = num;
            }
        }
    }

    void print() const{
        for(size_t k=0;k<this->shape_[2];++k) {
            for(size_t i=0;i<this->shape_[0];++i) {
                for(size_t j=0;j<this->shape_[1];++j)
                    std::cout<<(*this)(i,j,k)<<" ";
                std::cout<<std::endl;
            }
            
            std::cout<<std::endl;
        }
    }

    std::vector<size_t> getsize() const {
        return this->shape_;
    }

    Tensor operator+ (const Tensor& mat) const {
        // assert()
        Tensor temp(std::vector<size_t> {this->shape_[0],this->shape_[1],this->shape_[2]});
        for(size_t k=0; k<this->shape_[2]; ++k) {
            for(size_t i=0;i<this->shape_[0];++i) {
                for(size_t j=0;j<this->shape_[1];++j)
                    temp(i,j,k) = (*this)(i,j,k) + mat(i,j,k);
            }
        }

        return temp;
    }
    Tensor operator- (const Tensor& mat) const {
        // assert()
        Tensor temp(std::vector<size_t> {this->shape_[1],this->shape_[0],this->shape_[2]});
        for(size_t k=0; k<this->shape_[2]; ++k) {
            for(size_t i=0;i<this->shape_[0];++i) {
                for(size_t j=0;j<this->shape_[1];++j)
                    temp(i,j,k) = (*this)(i,j,k) - mat(i,j,k);
            }
        }

        return temp;
    }
    Tensor operator* (const Tensor& mat) const {
        return this->dot(mat);
    }
    Tensor operator* (const float& num) const {
        Tensor temp(std::vector<size_t> {this->shape_[1],this->shape_[0],this->shape_[2]});
        for(size_t k=0; k<this->shape_[2]; ++k) {
            for(size_t i=0;i<this->shape_[0];++i) {
                for(size_t j=0;j<this->shape_[1];++j)
                    temp(i,j,k) = num * (*this)(i,j,k);
            }
        }

        return temp;
    }
    Tensor operator+= (Tensor mat) {
        (*this) = (*this) + mat;
        return (*this);
    }
    Tensor operator-= (Tensor mat) {
        (*this) = (*this) - mat;
        return (*this);
    }


private:
    std::vector<size_t> shape_;
    std::vector<T> data_;
};
