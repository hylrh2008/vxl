#ifndef vsol_tetrahedron_h_
#define vsol_tetrahedron_h_
//*****************************************************************************
//:
//  \file
// \brief tetrahedral volume in 3D space
//
// The vertices order gives the orientation of the tetrahedron
//
// \author
// Peter Vanroose, 5 July 2000.
//*****************************************************************************

class vsol_tetrahedron;

//*****************************************************************************
// External declarations for values
//*****************************************************************************
#include "vsol_tetrahedron_sptr.h"
#include "vsol_polyhedron.h"
#include "vsol_point_3d.h"

class vsol_tetrahedron
  :public vsol_polyhedron
{
  //***************************************************************************
  // Initialization
  //***************************************************************************
public:
  //---------------------------------------------------------------------------
  //: Constructor from its 4 vertices
  //---------------------------------------------------------------------------
  explicit vsol_tetrahedron(const vsol_point_3d_sptr &new_p0,
                            const vsol_point_3d_sptr &new_p1,
                            const vsol_point_3d_sptr &new_p2,
                            const vsol_point_3d_sptr &new_p3);

  //---------------------------------------------------------------------------
  //: Copy constructor
  //---------------------------------------------------------------------------
  vsol_tetrahedron(const vsol_tetrahedron &other);

  //---------------------------------------------------------------------------
  //: Destructor
  //---------------------------------------------------------------------------
  virtual ~vsol_tetrahedron() {}

  //---------------------------------------------------------------------------
  //: Clone `this': creation of a new object and initialization
  //  See Prototype pattern
  //---------------------------------------------------------------------------
  virtual vsol_spatial_object_3d_sptr clone(void) const { return new vsol_tetrahedron(*this); }

  //***************************************************************************
  // Access
  //***************************************************************************

  //---------------------------------------------------------------------------
  //: Return the first vertex
  //---------------------------------------------------------------------------
  virtual vsol_point_3d_sptr p0(void) const;

  //---------------------------------------------------------------------------
  //: Return the second vertex
  //---------------------------------------------------------------------------
  virtual vsol_point_3d_sptr p1(void) const;

  //---------------------------------------------------------------------------
  //: Return the third vertex
  //---------------------------------------------------------------------------
  virtual vsol_point_3d_sptr p2(void) const;

  //---------------------------------------------------------------------------
  //: Return the last vertex
  //---------------------------------------------------------------------------
  virtual vsol_point_3d_sptr p3(void) const;

  //***************************************************************************
  // Comparison
  //***************************************************************************

  //---------------------------------------------------------------------------
  //: Has `this' the same points than `other' and the same orientation ?
  //---------------------------------------------------------------------------
  virtual bool operator==(const vsol_tetrahedron &other) const;
  inline bool operator!=(const vsol_tetrahedron &other)const{return !operator==(other);}
  virtual bool operator==(const vsol_polyhedron &other) const; // virtual of vsol_polyhedron
  virtual bool operator==(const vsol_spatial_object_3d& obj) const; // virtual of vsol_spatial_object_3d

  //***************************************************************************
  // Status report
  //***************************************************************************

  //---------------------------------------------------------------------------
  //: Return the volume of `this'
  //---------------------------------------------------------------------------
  virtual double volume(void) const;

  //***************************************************************************
  // Element change
  //***************************************************************************

  //---------------------------------------------------------------------------
  //: Set the first vertex
  //---------------------------------------------------------------------------
  void set_p0(vsol_point_3d_sptr new_p0);

  //---------------------------------------------------------------------------
  //: Set the second vertex
  //---------------------------------------------------------------------------
  void set_p1(vsol_point_3d_sptr new_p1);

  //---------------------------------------------------------------------------
  //: Set the third vertex
  //---------------------------------------------------------------------------
  void set_p2(vsol_point_3d_sptr new_p2);

  //---------------------------------------------------------------------------
  //: Set the last vertex
  //---------------------------------------------------------------------------
  void set_p3(vsol_point_3d_sptr new_p3);

  //***************************************************************************
  // Basic operations
  //***************************************************************************

  //---------------------------------------------------------------------------
  //: Is `p' in `this' ?
  //---------------------------------------------------------------------------
  virtual bool in(vsol_point_3d const &p) const;
};

#endif // vsol_tetrahedron_h_
