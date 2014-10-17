#ifndef boxm2_vecf_ocl_transform_scene_h
#define boxm2_vecf_ocl_transform_scene_h
//:
// \file
// \brief A function to transform a scene
// \author J.L. Mundy
// \date October 5, 2014
//
#include <vbl/vbl_ref_count.h>
#include <boxm2/io/boxm2_cache.h>
#include <bocl/bocl_mem.h>
#include <vgl/vgl_vector_3d.h>
#include <vil/vil_image_view.h>
#include <bocl/bocl_device.h>
#include <boxm2/ocl/boxm2_opencl_cache2.h>
#include <boxm2/ocl/boxm2_opencl_cache.h>
#include <vgl/algo/vgl_rotation_3d.h>
#include <boxm2/ocl/algo/boxm2_ocl_camera_converter.h>
//: Map a scene with Euclidean and anisotropic scale transforms.
// the input transform is the inverse so that the target scene voxels
// are mapped backwards to extract the data from the source
// thus each target voxel is defined if the inverse transform lands on a
// valid source voxel.
class boxm2_vecf_ocl_transform_scene : public vbl_ref_count
{
 public:
  //: Constructor. 
  boxm2_vecf_ocl_transform_scene(boxm2_scene_sptr& source_scene,
				 boxm2_scene_sptr& target_scene,
				 boxm2_opencl_cache2_sptr ocl_cache);

  ~boxm2_vecf_ocl_transform_scene();

  unsigned ni() const{return  cl_ni;}
  unsigned nj() const{return  cl_nj;}

  //: transform a scene of arbitray size, block by block
  bool transform(vgl_rotation_3d<double>  rot,
		 vgl_vector_3d<double> trans,
		 vgl_vector_3d<double> scale);

  //: transform a scene with one block so that
  //  both source and target blocks fit in GPU memory
  //  if "finish==true" then GPU state is cleared
  //  and kernel args are released after target
  //  is transformed. The target data is written to disk.
  bool transform_1_blk(vgl_rotation_3d<double>  rot,
		       vgl_vector_3d<double> trans,
		       vgl_vector_3d<double> scale,
		       bool finish = true);

  //render the current state of the target scene
  bool render_scene_appearance(vpgl_camera_double_sptr const & cam, vil_image_view<float>& expected_img,
			       vil_image_view<float>& vis_img, int ni, int nj, bool finish = false);
 protected:
  bool compile_trans_kernel();
  bool compile_rend_kernel();
  bool compile_norm_kernel();
  bool init_ocl_trans();
  bool get_scene_appearance(boxm2_scene_sptr scene,
			    vcl_string&      options);

  boxm2_opencl_cache2_sptr  opencl_cache_;
  boxm2_scene_sptr target_scene_;
  boxm2_scene_sptr source_scene_;
  bocl_device_sptr device_;
  int apptypesize_;//both scenes should have the same apptype
  vcl_string app_type_;
  bocl_kernel * trans_kern;
  //transform kernel args 
  float* translation_buff;
  float* rotation_buff;
  float* scale_buff;
  bocl_mem* translation;
  bocl_mem* rotation;
  bocl_mem* scalem;
  bocl_mem_sptr centerX;
  bocl_mem_sptr centerY;
  bocl_mem_sptr centerZ;
  bocl_mem_sptr lookup;
  bocl_mem_sptr output;
  float output_buff[1000];
  bocl_mem* ocl_depth;
  bocl_mem* blk_info_target;
  bocl_mem* blk_info_source;
  boxm2_scene_info* info_buffer;
  bocl_mem* blk_target;
  bocl_mem* alpha_target;
  bocl_mem * mog_target;
  boxm2_scene_info* info_buffer_source;
  bocl_mem* blk_source;
  bocl_mem* alpha_source;
  bocl_mem* mog_source;
  // expected image kernel args
  float* buff;
  float* vis_buff;
  float* max_omega_buff;
  bocl_mem_sptr ray_o_buff;
  bocl_mem_sptr ray_d_buff;
  bocl_kernel * rend_kern;
  bocl_kernel * norm_kern;
  bocl_mem* exp_image;
  bocl_mem* vis_image;
  bocl_mem* max_omega_image;
  bocl_mem* exp_img_dim;
  unsigned cl_ni;
  unsigned cl_nj;
  bocl_mem* tnearfar_mem_ptr;
  cl_command_queue queue;
};

#endif


