template <typename T>
class Metrics {
	public:
	virtual T compute(const Tensor<T>& pred,const Tensor<T>& target) = 0;
	virtual ~Metrics() {}
};

template <typename T>
class Accuracy: public Metrics<T> {
	public:
	T compute(const Tensor<T>& pred,const Tensor<T>& target) override {
		int num_correct = 0;
		for (size_t i = 0; i < pred.getsize()[0]; i++) {
			bool correct = true;
			for (size_t j = 0; j < pred.getsize()[1]; j++) {
				if (std::round(pred(i, j, 0)) != target(i, j, 0)) {
					correct = false;
					break;
				}
			}

			if (correct) {
				num_correct++;
			}
		}
		T accuracy = (float)num_correct / pred.getsize()[0];
		return accuracy;
	}
};