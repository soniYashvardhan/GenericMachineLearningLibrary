template<typename T>
class Model {
	public:
	Model():nlayers(0) {}

	void add_layer(Layer<T>* layer) {
		// std::cout<<(typeid(*layer)==typeid(Dense<T>))<<std::endl;
		layers.push_back(layer);
		++nlayers;
	}
	void compile(const std::string& loss) {
        if(loss == "CategoricalCrossentropy")
            lossfunc = new MeanSquaredError<T>();
        else if(loss=="MeanSquaredError")
            lossfunc = new MeanSquaredError<T>();
        else if(loss=="BinaryCrossentropy")
            lossfunc = new MeanSquaredError<T>();
        else
            throw std::runtime_error("No such loss function");
	}
	// void fit(const Tensor<T>& input, const Tensor<T>& target, size_t batch_size, size_t epochs, float learning_rate) {
	// 	size_t epoch = 0;
	// 	size_t batch=0;
	// 	std::vector<Tensor<T>* >ips (nlayers);
	// 	std::vector<Tensor<T>* >ops (nlayers);


	// 	// while(epoch<epochs) {
	// 	// 	// for(int i=0;i<input.getsize()[0]/batch_size;++i) {
	// 	// 	// 	batch = 0;
	// 	// 	// 	while(batch<batch_size) {

	// 	// 	// 	}
	// 	// 	// }
	// 	// 	ips[layer] = input;
	// 	// 	for(int layer=0; layer<nlayers; ++layer) {
	// 	// 		layer.forward(input, )
	// 	// 	}
	// 	// 	++epoch;
	// 	// }
	// };

	void fit(const Tensor<T> &input, const Tensor<T> &target, size_t batch_size, size_t epochs, float learning_rate) {
        Tensor<T> batch_input(std::vector<size_t> ({batch_size, input.getsize()[1], 1}));
        for (size_t i = 1; i <= epochs; i++) {
            // batch calculations
            size_t count = 0;
            size_t batch_count = std::ceil((float)input.getsize()[0] / batch_size);
            size_t j = 0;
            while (count < batch_count) {
                layers_ip.clear();
        //         // current batch formation
                for (size_t k = j; k < (j + batch_size) && k < input.getsize()[0]; k++) {
                    for (size_t l = 0; l < input.getsize()[1]; l++) {
                        batch_input(k - j, l, 0) = input(k, l, 0);
                    }
                }

                // forward
                Tensor<T>layer_input(batch_input);
                Tensor<T>layer_output(std::vector<size_t>({batch_size, layers[0]->getsize()[1], 1}));
                for (size_t x = 0; x < layers.size(); x++)
                {
                    Layer<T> *layer = layers[x];
                    layers_ip.push_back(layer_input);
                    layer->forward(layer_input, layer_output);
                    // layer_output.print();
                    layer_input = layer_output;
                    if (x == layers.size() - 1)
                        break;
                    else
                        layer_output = Tensor<T> (std::vector<size_t> {layers[x + 1]->getsize()[1], batch_size, 1});
                }
                // layer_output.print();
                // error calculation and accuracy computation
                T loss = lossfunc->compute(layer_output, target);
                // std::cout<<"Loss func:    "<<lossfunc->computed_loss<<std::endl;
                Accuracy<float> a;
                std::cout << "Epoch : " << i << "/" << epochs << ".........."<< "loss : " << loss <<".......Accuracy : "<<a.compute(layer_output,target)<<std::endl;

                Tensor<T> gradient(std::vector<size_t> {layer_output.getsize()[0], layer_output.getsize()[1], 1});
                lossfunc->compute_gradient(layer_output, target, gradient); // dy_hat calculation or da_last_layer
                // back propagation
                for (size_t y = layers.size() - 1; y>0; y--) {
                    // std::cout<<std::endl<<"layer: "<<y<<std::endl;
                    Layer<T> *layer = layers[y];
                    layer_input = layers_ip[y];
                    Tensor<T> input_gradient = Tensor<T>(std::vector<size_t>({batch_size, layers[y - 1]->getsize()[1], 1}));
                    layer->backward(layer_input, gradient, input_gradient);
                    // weight updation
                    layer->update_weights(learning_rate);
                    gradient = input_gradient;
                }
                // std::cout<<std::endl<<"layer: "<<0<<std::endl;
                Layer<T> *layer = layers[0];
                layer_input = layers_ip[0];
                Tensor<T> input_gradient = Tensor<T>(std::vector<size_t> {batch_size, layer_input.getsize()[0], 1});
                layer->backward(layer_input, gradient, input_gradient);
                layer->update_weights(learning_rate);
                j = j + batch_size;
                count++;
            }
        }
    }


	void predict(const Tensor<T>& input, Tensor<T>& output);

	private:
	std::vector<Layer<T>*> layers;
    std::vector<Tensor<T>> layers_ip;
	int nlayers;
	LossFunction<T>* lossfunc;

};