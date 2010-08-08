// This is vpgl/ihog/ihog_cost_func.h
#ifndef ihog_cost_func_h_
#define ihog_cost_func_h_
//:
// \file
// \brief A cost function for registering video frames
//        by minimizing square difference in intensities
// \author Matt Leotta
// \date 4/13/04
//
// \verbatim
//  Modifications
//   None
// \endverbatim

#include <vnl/vnl_vector.h>
#include <vnl/vnl_cost_function.h>
#include <vil/vil_image_view.h>
#include <ihog/ihog_world_roi.h>
#include <vimt/vimt_image_2d_of.h>
#include <vimt/vimt_transform_2d.h>

//: A cost function for registering video frames
// by minimizing square difference in intensities
class ihog_cost_func : public vnl_cost_function
{
public:
  //: Constructor
  ihog_cost_func( const vil_image_view<float>& image1,
                   const vil_image_view<float>& image2,
                   const ihog_world_roi& roi,
                   const vimt_transform_2d& init_xform );
   ihog_cost_func( const vil_image_view<float>& image1,
                   const vil_image_view<float>& image2,
                        const vil_image_view<float>& mask,
                        const ihog_world_roi& roi,
                        const vimt_transform_2d& init_xform );
  //: The main function.
  virtual double f(vnl_vector<double> const& x);

  //: Returns the transformed second image
  vil_image_view<float> last_xformed_image();


protected:
  vimt_image_2d_of<float> from_image_;
  vimt_image_2d_of<float> to_image_;
  ihog_world_roi roi_;
  vimt_transform_2d::Form form_;
  vil_image_view<bool> mask_image_;

};

#endif // ihog_cost_func_h_

