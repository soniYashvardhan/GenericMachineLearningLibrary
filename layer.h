template<typename T>
class Layer {
public:
    virtual void forward(const Tensor<T>& input, Tensor<T>& output) = 0;
    virtual void backward(const Tensor<T>& input, Tensor<T>& output_gradient, Tensor<T>& input_gradient) = 0;
    virtual void update_weights(float learning_rate) = 0;
    virtual std::vector<size_t> getsize() = 0;
    virtual ~Layer() {}
};
