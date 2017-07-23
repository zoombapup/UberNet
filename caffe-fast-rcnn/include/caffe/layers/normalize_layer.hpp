#ifndef CAFFE_NRM_LAYER_HPP_
#define CAFFE_NRM_LAYER_HPP_

#include <vector>

#include "caffe/blob.hpp"
#include "caffe/layer.hpp"
#include "caffe/proto/caffe.pb.h"

namespace caffe {

   /**
    * @brief Normalizes input.
    * https://github.com/kuprel/caffe
    */
   template <typename Dtype>
   class NormalizeLayer : public Layer<Dtype> {
    public:
     explicit NormalizeLayer(const LayerParameter& param)
         : Layer<Dtype>(param) {}
     virtual void LayerSetUp(const vector<Blob<Dtype>*>& bottom,
         const vector<Blob<Dtype>*>& top);
     virtual void Reshape(const vector<Blob<Dtype>*>& bottom,
         const vector<Blob<Dtype>*>& top);

     virtual inline const char* type() const { return "Normalize"; }
     virtual inline int ExactNumBottomBlobs() const { return 1; }
     virtual inline int ExactNumTopBlobs() const { return 1; }
     //virtual inline DiagonalAffineMap<Dtype> coord_map() {
     //  return DiagonalAffineMap<Dtype>::identity(2);
     //}

    protected:
     virtual void Forward_cpu(const vector<Blob<Dtype>*>& bottom,
         const vector<Blob<Dtype>*>& top);
     virtual void Forward_gpu(const vector<Blob<Dtype>*>& bottom,
         const vector<Blob<Dtype>*>& top);
     virtual void Backward_cpu(const vector<Blob<Dtype>*>& top,
         const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom);
     virtual void Backward_gpu(const vector<Blob<Dtype>*>& top,
        const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom);

     Blob<Dtype> norm_;
     Blob<Dtype> sum_channel_multiplier_, sum_spatial_multiplier_;
     Blob<Dtype> buffer_, buffer_channel_, buffer_spatial_;
     bool across_spatial_;
     bool channel_shared_;
     Dtype eps_;
   };

  }  // namespace caffe

#endif  // CAFFE_NRM_LAYER_HPP_
