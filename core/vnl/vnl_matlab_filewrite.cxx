#ifdef __GNUC__
#pragma implementation
#endif

#include <vcl/vcl_iostream.h> // must be first
#include "vnl_matlab_filewrite.h"

#include <vcl/vcl_fstream.h>
#include <vcl/vcl_strstream.h>

#include <vnl/vnl_complex.h>
#include <vnl/vnl_vector.h>
#include <vnl/vnl_matrix.h>
#include <vnl/vnl_matlab_write.h>

vnl_matlab_filewrite::vnl_matlab_filewrite(char const *file_name,
					   char const *basename VCL_DEFAULT_VALUE(0)) 
  : basename_(basename ? basename : "targetvar"), variable_int_(0), out_(file_name) 
{ 
  if (out_.bad())
    vcl_cerr << __FILE__ ":" << __LINE__ << ", WARNING : output stream is bad" << vcl_endl;
}

vcl_string vnl_matlab_filewrite::make_var_name(char const* variable_name)
{
  if (variable_name)
    return vcl_string(variable_name);
  else {
    ostrstream ss;
    ss << variable_int_++;    
    return basename_ + vcl_string(ss.str());
  }
}

//--------------------------------------------------------------------------------

//: scalar
void vnl_matlab_filewrite::write(double v, char const* variable_name) {
  vnl_matlab_write(out_, v, make_var_name(variable_name).c_str());
}

//: vector
void vnl_matlab_filewrite::write(vnl_vector<double> const& v, char const* variable_name) {
  vnl_matlab_write(out_, v.data_block(), v.size(), make_var_name(variable_name).c_str());
}

void vnl_matlab_filewrite::write(vnl_vector<vnl_double_complex> const& v, char const* variable_name) {
  vnl_matlab_write(out_, v.data_block(), v.size(), make_var_name(variable_name).c_str());
}

//: matrix
void vnl_matlab_filewrite::write(vnl_matrix<float> const& M, char const* variable_name) {
  vnl_matlab_write(out_, M.data_array(), M.rows(), M.cols(), make_var_name(variable_name).c_str());
}

void vnl_matlab_filewrite::write(vnl_matrix<double> const& M, char const* variable_name) {
  vnl_matlab_write(out_, M.data_array(), M.rows(), M.cols(), make_var_name(variable_name).c_str());
}

void vnl_matlab_filewrite::write(vnl_matrix<vnl_float_complex> const& M, char const* variable_name) {
  vnl_matlab_write(out_, M.data_array(), M.rows(), M.cols(), make_var_name(variable_name).c_str());
}

void vnl_matlab_filewrite::write(vnl_matrix<vnl_double_complex> const& M, char const* variable_name) {
  vnl_matlab_write(out_, M.data_array(), M.rows(), M.cols(), make_var_name(variable_name).c_str());
}
