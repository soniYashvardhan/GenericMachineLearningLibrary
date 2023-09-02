#include <typeinfo>
template<typename T>
class Dense : public Layer<T> {
public:
    Dense(size_t input_size, size_t output_size, std::string activation="sigmoid"): weights_(Tensor<T> (std::vector<size_t> {input_size, output_size,1})), 
    biases_(Tensor<T> (std::vector<size_t> {1, output_size, 1})), activation_(activation){
        // initialize weights and biases
        this->input_size = input_size;
        this->output_size = output_size;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis(0.0, 1.0/std::sqrt(input_size));
        for (size_t i = 0; i < input_size; ++i) {
            for (size_t j = 0; j < output_size; ++j) {
                weights_(i, j, 0) = dis(gen);
            }
        }
        biases_.fill(0.0);

        if(this->activation_ == "sigmoid") {
            act = new sigmoid<T>();
        }
    }
    void forward(const Tensor<T>& input, Tensor<T>& output) override {
        output = input.dot(weights_) + biases_;
        act->activate(output);
    }
    void backward(const Tensor<T>& input, Tensor<T>& output_gradient, Tensor<T>& input_gradient) override {
        // std::cout<<"input size: "<<input.getsize()[0]<<" "<<input.getsize()[1]<<std::endl;
        // std::cout<<"output_grad size: "<<output_gradient.getsize()[0]<<" "<<output_gradient.getsize()[1]<<std::endl;
        // std::cout<<"input_grad size: "<<input_gradient.getsize()[0]<<" "<<input_gradient.getsize()[1]<<std::endl;
        // std::cout<<"weights size: "<<weights_.getsize()[0]<<" "<<weights_.getsize()[1]<<std::endl;
        // std::cout<<"biases size: "<<biases_.getsize()[0]<<" "<<biases_.getsize()[1]<<std::endl<<std::endl;
        act->activate_diff(output_gradient);
        input_gradient = weights_.transpose();
        input_gradient = output_gradient.dot(input_gradient);
        // std::cout<<"input grd: "<<std::endl;
        // input_gradient.print();
        weight_gradient_ = input.transpose();
        weight_gradient_ = weight_gradient_.dot(output_gradient);
        bias_gradient_ = output_gradient.sum();
    }
    void update_weights(float learning_rate) override {
        Tensor<T> temp1 = weight_gradient_ * learning_rate;
        weights_ -= temp1;
        Tensor<T> temp2 = bias_gradient_ * learning_rate;
        biases_ = biases_ - temp2;
    }
    
    std::vector<size_t> getsize() override {
        return {this->input_size, this->output_size};
    }

private:
    Tensor<T> weights_;
    Tensor<T> biases_;
    Tensor<T> weight_gradient_;
    Tensor<T> bias_gradient_;
    std::string activation_;
    Activation<T>* act;
public:
    size_t input_size;
    size_t output_size;
};
