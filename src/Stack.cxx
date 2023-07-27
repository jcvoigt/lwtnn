#include "lwtnn/Stack.hh"
#include <Eigen/Dense>

namespace lwt
{
  // Definitions for double overloads
  ILayer* get_raw_activation_layer(ActivationConfig activation) {
    return generic::get_raw_activation_layer<double>(activation);
  }

  std::function<double(double)> get_activation(lwt::ActivationConfig act) {
    return generic::get_activation<double>(act);
  }

  double nn_sigmoid( double x ) {
    return generic::nn_sigmoid<double>(x);
  }

  double nn_hard_sigmoid( double x ) {
    return generic::nn_hard_sigmoid<double>(x);
  }

  double nn_tanh( double x ) {
    return generic::nn_tanh<double>(x);
  }

  double nn_relu( double x) {
    return generic::nn_relu<double>(x);
  }

  MatrixX<double> build_matrix(const std::vector<double>& weights, std::size_t n_inputs) {
    return generic::build_matrix<double, double>(weights, n_inputs);
  }

  VectorX<double> build_vector(const std::vector<double>& bias) {
    return generic::build_vector<double, double>(bias);
  }

  DenseComponents get_component(const lwt::LayerConfig& layer, std::size_t n_in) {
    return generic::get_component<double>(layer, n_in);
  }

  // consistency checks
  void throw_if_not_maxout(const LayerConfig& layer) {
    bool wt_ok = layer.weights.size() == 0;
    bool bias_ok = layer.bias.size() == 0;
    bool maxout_ok = layer.sublayers.size() > 0;
    bool act_ok = layer.activation.function == Activation::NONE;
    if (wt_ok && bias_ok && maxout_ok && act_ok) return;
    throw NNConfigurationException("layer has wrong info for maxout");
  }
  void throw_if_not_dense(const LayerConfig& layer) {
    if (layer.sublayers.size() > 0) {
      throw NNConfigurationException("sublayers in dense layer");
    }
  }

  void throw_if_not_conv1d(const LayerConfig& layer, std::size_t n_inputs) {
    bool arch_ok = layer.architecture == Architecture::CONV1D;
    bool bias_ok = layer.bias.size() > 0;
    bool weights_ok = layer.weights.size() > 0 && layer.weights.size() % (n_inputs*layer.bias.size()) == 0;
    bool sublayer_ok = layer.sublayers.size() == 0;
    if (arch_ok && bias_ok && weights_ok && sublayer_ok) return;
    throw NNConfigurationException("layer has wrong info for conv1d");
  }

  void throw_if_not_normalization(const LayerConfig& layer) {
    if (layer.sublayers.size() > 0) {
      throw NNConfigurationException("sublayers in normalization layer");
    }
  }
}
