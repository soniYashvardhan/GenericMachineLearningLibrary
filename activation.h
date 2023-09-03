template <typename T>
class Activation {
	public:
	virtual ~Activation() {}
	virtual void activate(Tensor<T>& output) = 0;
	virtual void activate_diff(Tensor<T>& output) = 0;
	Tensor<T> z; //z = wa+b
};

template <typename T>
class sigmoid: public Activation<T> {
	void activate(Tensor<T>& output) {
		for(int i=0;i<output.getsize()[0];++i) {
			for(int j=0;j<output.getsize()[1];++j)
				output(i,j,0) = static_cast<T>(1 / (1 + exp( (-1)*output(i,j,0) )));
		}

		this->z = output;
	}

	void activate_diff(Tensor<T> &output) {
		for(int i=0;i<output.getsize()[0];++i) {
			for(int j=0;j<output.getsize()[1];++j)
				output(i,j,0) = static_cast<T>((this->z)(i,j,0)) * (1 - (this->z)(i,j,0));
		}
	}
};

template <typename T>
class relu: public Activation<T> {
	void activate(Tensor<T>& output) {
		for(int i=0;i<output.getsize()[0];++i) {
			for(int j=0;j<output.getsize()[1];++j)
				output(i,j,0) = std::max(static_cast<T>(0), output(i,j,0));
		}

		this->z = output;
	}

	void activate_diff(Tensor<T> &output) {
		for(int i=0;i<output.getsize()[0];++i) {
			for(int j=0;j<output.getsize()[1];++j) {
				if(this->z(i,j,0) <= 0)
					output(i,j,0) = 0;
				else
					output(i,j,0) = 1;
			}
		}
	}
};

template <typename T>
class softmax: public Activation<T> {
	void activate(Tensor<T>& output) {
		Tensor<T> temp(std::vector<size_t>({output.getsize()[0], 1, 1}));

		for (size_t i = 0; i < output.getsize()[0]; i++) {
			for (size_t j = 0; j < output.getsize()[1]; j++) {
				temp(i, 0, 0) = temp(i, 0, 0) + std::exp(output(i, j, 0));
			}
		}
		for (size_t i = 0; i < output.getsize()[0]; i++) {
			for (size_t j = 0; j < output.getsize()[1]; j++) {
				output(i, j, 0) = std::exp(output(i, j, 0)) / temp(i, 0, 0);
			}
		}
		this->z = output;
	}

	void activate_diff(Tensor<T> &output) {
		Tensor<T>computed_gradient(std::vector<size_t>({output.getsize()[0],output.getsize()[1],1}));
		
		for (size_t i = 0; i < output.getsize()[0]; ++i) {
			for (size_t j = 0; j < output.getsize()[1]; ++j) {
				T sum = 0;
				for (size_t k = 0; k < output.getsize()[1]; ++k) {
					T softmax_derivative = (j == k) ? this->z(i,k,0) * (1.0 - this->z(i,k,0)) : -this->z(i,k,0) * this->z(i,j,0);
					sum += (output(i,k,0) * softmax_derivative);
				}
				computed_gradient(i,j,0) = sum;
			}
		}
		output = computed_gradient;
	}
};