template<typename T>
class LossFunction {
public:
    virtual T compute(const Tensor<T>& predicted, const Tensor<T>& target) = 0;
    virtual void compute_gradient(const Tensor<T>& predicted, const Tensor<T>& target, Tensor<T>& gradient) = 0;
    virtual ~LossFunction() {}
public:
    T computed_loss;
};

// template<typename T>
// class CategoricalCrossentropy : public LossFunction<T> {
// public:
//     T compute(const Tensor<T> &predicted, const Tensor<T> &target) override
//     {
//         T loss = 0;
//         for(size_t i =0; i<predicted.shape[0]; i++)
//         {
//             for(size_t j=0;j<predicted.shape[1];j++)
//             {
//                 loss-=target(i,j,0) * log(predicted(i,j,0));
//             }
//         }
//         this->computed_loss = loss/static_cast<T>(predicted.shape[1]);
//         return abs(this->computed_loss);
//     }
//     void compute_gradient(const Tensor<T> &predicted, const Tensor<T> &target, Tensor<T> &gradient) override
//     {
//         for(size_t i =0;i<predicted.shape[0];i++)
//         {
//             for(size_t j=0;j<predicted.shape[1];j++)
//             {
//                gradient(i,j,0) =(target(i,j,0)/predicted(i,j,0));
//             }
//         }
//     }
// };


template<typename T>
class MeanSquaredError : public LossFunction<T> {
	public:
	T compute(const Tensor<T> &predicted, const Tensor<T> &target) override {
        T loss = 0;
        for(size_t i =0;i<predicted.getsize()[0];i++) {
            for(size_t j=0;j<predicted.getsize()[1];j++) {
                loss+=std::pow((predicted(i,j,0) - target(i,j,0)),2);
            }
        }

        return this->computed_loss = loss/static_cast<T>(predicted.getsize()[0]);
    }

    void compute_gradient(const Tensor<T> &predicted, const Tensor<T> &target, Tensor<T> &gradient) override {
        T temp = 0;
        for(size_t i =0;i<predicted.getsize()[0];i++) {
            for(size_t j=0;j<predicted.getsize()[1];j++) {
               temp = predicted(i,j,0) - target(i,j,0);
               gradient(i,j,0)=(2/static_cast<T>(predicted.getsize()[0]))*temp;
            }
        }
    }

};

// template <typename T>
// T BinaryCrossentropy<T>::compute(const Tensor<T> &predicted, const Tensor<T> &target)
// {
//     T loss = 0;
//     for (size_t i = 0; i < predicted.shape[1]; i++)
//     {
//         loss -= target(0, i, 0) * log(predicted(0, i, 0)) + (1 - target(0, i, 0)) * log(1 - predicted(0, i, 0));
//     }
//     loss /= predicted.shape[1];
//     // cout << "Predicted: " << predicted(0,0,0) << endl;
//     // cout << "Target: " << target(0,0,0) << endl;
//     // cout << "Loss: " << loss << endl;
//     return loss;
// }

// template <typename T>
// void BinaryCrossentropy<T>::compute_gradient(const Tensor<T> &predicted, const Tensor<T> &target, Tensor<T> &gradient)
// {
//     for (size_t i = 0; i < predicted.shape[1]; i++)
//     {
//         gradient(0, i, 0) = (predicted(0, i, 0) - target(0, i, 0)) / ((1 - (target(0, i, 0)) * predicted(0, i, 0)) + (target(0, i, 0) * (1 - predicted(0, i, 0))) + 1e-8);
//         // cout << "Gradient: " << gradient(0,0,0) << endl;
//     }
// }

