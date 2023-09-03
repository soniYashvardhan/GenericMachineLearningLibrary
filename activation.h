template <typename T>
class Activation {
	public:
	virtual ~Activation() {}
	virtual void activate(Tensor<T>& output) = 0;
	virtual void activate_diff(Tensor<T>& output) = 0;
	Tensor<T> z;
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
				if(output(i,j,0) <= 0)
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