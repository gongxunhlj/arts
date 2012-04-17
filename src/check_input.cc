/* Copyright (C) 2002-2008
   Patrick Eriksson <patrick.eriksson@chalmers.se>
   Stefan Buehler   <sbuehler@ltu.se>

   This program is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the
   Free Software Foundation; either version 2, or (at your option) any
   later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307,
   USA. */



/*===========================================================================
  === File description 
  ===========================================================================*/

/*!
  \file   check_input.cc
  \author Patrick Eriksson <Patrick.Eriksson@chalmers.se>
  \date 2002-04-15 

  General functions to check the size and logic of input to functions.
*/



/*===========================================================================
  === External declarations
  ===========================================================================*/

#include <cmath>
#include <stdexcept>
#include "check_input.h"
#include "array.h"
#include "logic.h"
#include "gridded_fields.h"

extern const Index GFIELD3_P_GRID;
extern const Index GFIELD3_LAT_GRID;
extern const Index GFIELD3_LON_GRID;





/*===========================================================================
  === Functions for Index
  ===========================================================================*/

//! chk_if_bool 
/*! 
    Checks that a variable of type Index has the value 0 or 1.

    The function gives an error message if this is not the case.

    \param    x_name   The name of the variable.
    \param    x        A variable of type Index.

    \author Patrick Eriksson 
    \date   2002-04-15
*/
void chk_if_bool( 
        const String&   x_name,
        const Index&    x )
{
  if ( !is_bool(x) )
    {
      ostringstream os;
      os << "The variable *" << x_name <<  "* must be a boolean (0 or 1).\n" 
         << "The present value of *"<< x_name <<  "* is " << x << ".";
      throw runtime_error( os.str() );
    }
}

//! chk_if_in_range
/*! 
    Checks that a variable of type Index has a value inside the specified
    range.

    The function gives an error message if this is not the case.

    \param    x_name   The name of the variable.
    \param    x        A variable of type Index.
    \param    x_low    Lowest allowed value for x.
    \param    x_high   Highest allowed value for x.

    \author Patrick Eriksson 
    \date   2002-04-15
*/
void chk_if_in_range( 
        const String&   x_name,
        const Index&    x, 
        const Index&    x_low, 
        const Index&    x_high )
{
  if ( (x<x_low) || (x>x_high) )
    {
      ostringstream os;
      os << "The variable *" << x_name <<  "* must fulfill:\n"
         << "   " << x_low << " <= " << x_name << " <= " << x_high << "\n" 
         << "The present value of *"<< x_name <<  "* is " << x << ".";
      throw runtime_error( os.str() );
    }
}

//! chk_if_increasing
/*! 
    Checks if an ArrayOfIndex is strictly increasing. Cloned from
    Patricks similar function for Vector.

    Duplicated values are not allowed.

    The function gives an error message if this is not the case.

    \param    x_name   The name of the variable.
    \param    x        A variable of type ArrayOfIndex.

    \author Stefan Buehler
    \date   2007-05-18
*/
void chk_if_increasing( 
        const String&       x_name,
        const ArrayOfIndex& x ) 
{
  if ( !is_increasing(x) )
    {
      ostringstream os;
      os << "The ArrayOfIndex *" << x_name <<  "* must have strictly\n"
         << "increasing values, but this is not the case.\n";
      os << "x = " << x << "\n";
      throw runtime_error( os.str() );
    }
}





/*===========================================================================
  === Functions for Numeric
  ===========================================================================*/

//! chk_not_negative 
/*! 
    Checks that a variable of type Numeric is 0 or positive.

    The function gives an error message if this is not the case.

    \param    x_name   The name of the variable.
    \param    x        A variable of type Numeric.

    \author Patrick Eriksson 
    \date   2002-04-15
*/
void chk_not_negative( 
        const String&    x_name,
        const Numeric&   x ) 
{
  if ( x < 0 )
    {
      ostringstream os;
      os << "The variable *" << x_name <<  "* must be >= 0.\n"
         << "The present value of *"<< x_name <<  "* is " << x << ".";
      throw runtime_error( os.str() );
    }
}



//! chk_if_in_range
/*! 
    Checks that a variable of type Numeric has a value inside the specified
    range.

    The function gives an error message if this is not the case.

    \param    x_name   The name of the variable.
    \param    x        A variable of type Numeric.
    \param    x_low    Lowest allowed value for x.
    \param    x_high   Highest allowed value for x.

    \author Patrick Eriksson 
    \date   2002-04-15
*/
void chk_if_in_range( 
        const String&    x_name,
        const Numeric&   x, 
        const Numeric&   x_low, 
        const Numeric&   x_high )
{
  if ( (x<x_low) || (x>x_high) )
    {
      ostringstream os;
      os << "The variable *" << x_name <<  "* must fulfill:\n"
         << "   " << x_low << " <= " << x_name << " <= " << x_high << "\n" 
         << "The present value of *"<< x_name <<  "* is " << x << ".";
      throw runtime_error( os.str() );
    }
}





/*===========================================================================
  === Functions for Vector
  ===========================================================================*/

//! chk_vector_length
/*! 
    Checks that a vector has the specified length.

    The function gives an error message if this is not the case.

    \param    x_name   The name of the variable.
    \param    x        A variable of type Vector.
    \param    l        The expected length of x.

    \author Patrick Eriksson 
    \date   2002-04-15
*/
void chk_vector_length( 
        const String&      x_name,
        ConstVectorView    x,
        const Index&       l ) 
{
  if ( x.nelem() != l )
    {
      ostringstream os;
      os << "The vector *" << x_name <<  "* must have the length " << l 
         << ".\n" 
         << "The present length of *"<< x_name <<  "* is " << x.nelem() << ".";
      throw runtime_error( os.str() );
    }
}



//! chk_vector_length
/*! 
    Checks if two vectors have the same length.

    The function gives an error message if this is not the case.

    \param    x1_name   The name of the first vector
    \param    x2_name   The name of the second vector
    \param    x1        The first vector.
    \param    x2        The second vector.

    \author Patrick Eriksson 
    \date   2002-04-15
*/
void chk_vector_length( 
        const String&      x1_name,
        const String&      x2_name,
        ConstVectorView    x1, 
        ConstVectorView    x2 ) 
{
  if ( x1.nelem() != x2.nelem() )
    {
      ostringstream os;
      os << "The vectors *" << x1_name <<  "* and *" << x2_name 
         <<  "* must have the same length.\n"
         << "The length of *"<< x1_name <<  "* is " << x1.nelem() << ".\n"
         << "The length of *"<< x2_name <<  "* is " << x2.nelem() << ".";
      throw runtime_error( os.str() );
    }
}



//! chk_if_increasing
/*! 
    Checks if a vector is strictly increasing.

    Duplicated values are not allowed.

    The function gives an error message if this is not the case.

    \param    x_name   The name of the variable.
    \param    x        A variable of type Vector.

    \author Patrick Eriksson 
    \date   2002-04-15
*/
void chk_if_increasing( 
        const String&      x_name,
        ConstVectorView    x ) 
{
  if ( !is_increasing(x) )
    {
      ostringstream os;
      os << "The vector *" << x_name <<  "* must have strictly\n"
         << "increasing values, but this is not the case.\n";
      os << "x = " << x << "\n";
      throw runtime_error( os.str() );
    }
}



//! chk_if_decreasing
/*! 
    Checks if a vector is strictly decreasing.

    Duplicated values are not allowed.

    The function gives an error message if this is not the case.

    \param    x_name   The name of the variable.
    \param    x        A variable of type Vector.

    \author Patrick Eriksson 
    \date   2002-04-15
*/
void chk_if_decreasing( 
        const String&      x_name,
        ConstVectorView    x ) 
{
  if ( !is_decreasing(x) )
    {
      ostringstream os;
      os << "The vector *" << x_name <<  "* must have strictly\ndecreasing "
         << "values, but this is not the case.\n";
      throw runtime_error( os.str() );
    }
}



//! chk_if_equal
/*!
 * Checks if two vectors are equal within a margin.
 *
 * \param   x1_name The name of the first variable (used in error message).
 * \param   x2_name The name of the second variable (used in error message).
 * \param   v1      First vector
 * \param   v2      Second vector
 * \param   margin  uncertainty margin. Default: 1e-6
 *
 * \author  Gerrit Holl
 * \date    2011-05-04
*/

void chk_if_equal(
        const String&   x1_name,
        const String&   x2_name,
        ConstVectorView v1,
        ConstVectorView v2,
        Numeric         margin
        )
{
  chk_vector_length(x1_name, x2_name, v1, v2);

  for (Index i = 0; i<v1.nelem(); i++)
  {
    if (abs(v1[i] - v2[i]) > margin)
      {
        ostringstream os;
        os << "Vectors " << x1_name << " and " << x2_name 
           << " differ.\n"
           << x1_name << "[" << i << "]" << " = " << v1[i] << "\n"
           << x2_name << "[" << i << "]" << " = " << v2[i] << "\n"
           << "Difference should not exceed " << margin << "\n";
       throw runtime_error(os.str());
     }
  }
}





/*===========================================================================
  === Functions for Matrix
  ===========================================================================*/

//! chk_matrix_ncols
/*! 
    Checks that a matrix has the specified number of columns.

    The function gives an error message if this is not the case.

    \param    x_name   The name of the variable.
    \param    x        A matrix.
    \param    l        The expected length of x.

    \author Patrick Eriksson 
    \date   2002-05-16
*/
void chk_matrix_ncols( 
        const String&      x_name,
        ConstMatrixView    x,
        const Index&       l ) 
{
  if ( x.ncols() != l )
    {
      ostringstream os;
      os << "The matrix *" << x_name <<  "* must have " << l << " columns,\n"
         << "but the number of columns is " << x.ncols() << ".";
      throw runtime_error( os.str() );
    }
}



//! chk_matrix_nrows
/*! 
    Checks that a matrix has the specified number of rows.

    The function gives an error message if this is not the case.

    \param    x_name   The name of the variable.
    \param    x        A matrix.
    \param    l        The expected length of x.

    \author Patrick Eriksson 
    \date   2002-05-16
*/
void chk_matrix_nrows( 
        const String&      x_name,
        ConstMatrixView    x,
        const Index&       l ) 
{
  if ( x.nrows() != l )
    {
      ostringstream os;
      os << "The matrix *" << x_name <<  "* must have " << l << " rows,\n"
         << "but the number of rows is " << x.nrows() << ".";
      throw runtime_error( os.str() );
    }
}





/*===========================================================================
  === Functions for Tensors
  ===========================================================================*/

//! Runtime check for size of Vector.
/*! 
  This is the runtime version of is_size. An appropriate error message
  is generated if the size is not correct.

  \param    x_name   The name of the agenda.
  \param    x        A variable of type Agenda.
  \param    c        Required number of columns

  \author Stefan Buehler
  \date   2002-11-29
*/
void chk_size( const String&    x_name,
               ConstVectorView  x,
               const Index&     c ) 
{
  if ( !is_size(x,c) )
    {
      ostringstream os;
      os << "The object *" << x_name
         << "* does not have the right size.\n"
         << "Dimensions should be:"
         << " " << c 
         << ",\nbut they are:         "
         << " " << x.nelem()      
         << ".";
      throw runtime_error( os.str() );
    }
}

//! Runtime check for size of Matrix.
/*! 
  This is the runtime version of is_size. An appropriate error message
  is generated if the size is not correct.

  \param    x_name   The name of the agenda.
  \param    x        A variable of type Agenda.
  \param    r        Required number of rows
  \param    c        Required number of columns

  \author Stefan Buehler
  \date   2002-11-29
*/
void chk_size( const String&    x_name,
               ConstMatrixView  x,
               const Index&     r,
               const Index&     c ) 
{
  if ( !is_size(x,r,c) )
    {
      ostringstream os;
      os << "The object *" << x_name
         << "* does not have the right size.\n"
         << "Dimensions should be:"
         << " " << r 
         << " " << c 
         << ",\nbut they are:         "
         << " " << x.nrows()      
         << " " << x.ncols()      
         << ".";
      throw runtime_error( os.str() );
    }
}

//! Runtime check for size of Tensor.
/*! 
  This is the runtime version of is_size. An appropriate error message
  is generated if the size is not correct.

  \param    x_name   The name of the agenda.
  \param    x        A variable of type Agenda.
  \param    p        Required number of pages
  \param    r        Required number of rows
  \param    c        Required number of columns

  \author Stefan Buehler
  \date   2002-11-29
*/
void chk_size( const String&    x_name,
               ConstTensor3View x,
               const Index&     p,
               const Index&     r,
               const Index&     c ) 
{
  if ( !is_size(x,p,r,c) )
    {
      ostringstream os;
      os << "The object *" << x_name
         << "* does not have the right size.\n"
         << "Dimensions should be:"
         << " " << p 
         << " " << r 
         << " " << c 
         << ",\nbut they are:         "
         << " " << x.npages()     
         << " " << x.nrows()      
         << " " << x.ncols()      
         << ".";
      throw runtime_error( os.str() );
    }
}

//! Runtime check for size of Tensor.
/*! 
  This is the runtime version of is_size. An appropriate error message
  is generated if the size is not correct.

  \param    x_name   The name of the agenda.
  \param    x        A variable of type Agenda.
  \param    b        Required number of books
  \param    p        Required number of pages
  \param    r        Required number of rows
  \param    c        Required number of columns

  \author Stefan Buehler
  \date   2002-11-29
*/
void chk_size( const String&    x_name,
               ConstTensor4View x,
               const Index&     b,
               const Index&     p,
               const Index&     r,
               const Index&     c ) 
{
  if ( !is_size(x,b,p,r,c) )
    {
      ostringstream os;
      os << "The object *" << x_name
         << "* does not have the right size.\n"
         << "Dimensions should be:"
         << " " << b 
         << " " << p 
         << " " << r 
         << " " << c 
         << ",\nbut they are:         "
         << " " << x.nbooks()     
         << " " << x.npages()     
         << " " << x.nrows()      
         << " " << x.ncols()      
         << ".";
      throw runtime_error( os.str() );
    }
}

//! Runtime check for size of Tensor.
/*! 
  This is the runtime version of is_size. An appropriate error message
  is generated if the size is not correct.

  \param    x_name   The name of the agenda.
  \param    x        A variable of type Agenda.
  \param    s        Required number of shelves
  \param    b        Required number of books
  \param    p        Required number of pages
  \param    r        Required number of rows
  \param    c        Required number of columns

  \author Stefan Buehler
  \date   2002-11-29
*/
void chk_size( const String&    x_name,
               ConstTensor5View x,
               const Index&     s,
               const Index&     b,
               const Index&     p,
               const Index&     r,
               const Index&     c ) 
{
  if ( !is_size(x,s,b,p,r,c) )
    {
      ostringstream os;
      os << "The object *" << x_name
         << "* does not have the right size.\n"
         << "Dimensions should be:"
         << " " << s 
         << " " << b 
         << " " << p 
         << " " << r 
         << " " << c 
         << ",\nbut they are:         "
         << " " << x.nshelves()   
         << " " << x.nbooks()     
         << " " << x.npages()     
         << " " << x.nrows()      
         << " " << x.ncols()      
         << ".";
      throw runtime_error( os.str() );
    }
}

//! Runtime check for size of Tensor.
/*! 
  This is the runtime version of is_size. An appropriate error message
  is generated if the size is not correct.

  \param    x_name   The name of the agenda.
  \param    x        A variable of type Agenda.
  \param    v        Required number of vitrines
  \param    s        Required number of shelves
  \param    b        Required number of books
  \param    p        Required number of pages
  \param    r        Required number of rows
  \param    c        Required number of columns

  \author Stefan Buehler
  \date   2002-11-29
*/
void chk_size( const String&    x_name,
               ConstTensor6View x,
               const Index&     v,
               const Index&     s,
               const Index&     b,
               const Index&     p,
               const Index&     r,
               const Index&     c ) 
{
  if ( !is_size(x,v,s,b,p,r,c) )
    {
      ostringstream os;
      os << "The object *" << x_name
         << "* does not have the right size.\n"
         << "Dimensions should be:"
         << " " << v 
         << " " << s 
         << " " << b 
         << " " << p 
         << " " << r 
         << " " << c 
         << ",\nbut they are:         "
         << " " << x.nvitrines()  
         << " " << x.nshelves()   
         << " " << x.nbooks()     
         << " " << x.npages()     
         << " " << x.nrows()      
         << " " << x.ncols()      
         << ".";
      throw runtime_error( os.str() );
    }
}

//! Runtime check for size of Tensor.
/*! 
  This is the runtime version of is_size. An appropriate error message
  is generated if the size is not correct.

  \param    x_name   The name of the agenda.
  \param    x        A variable of type Agenda.
  \param    l        Required number of libraries
  \param    v        Required number of vitrines
  \param    s        Required number of shelves
  \param    b        Required number of books
  \param    p        Required number of pages
  \param    r        Required number of rows
  \param    c        Required number of columns

  \author Stefan Buehler
  \date   2002-11-29
*/
void chk_size( const String&    x_name,
               ConstTensor7View x,
               const Index&     l,
               const Index&     v,
               const Index&     s,
               const Index&     b,
               const Index&     p,
               const Index&     r,
               const Index&     c ) 
{
  if ( !is_size(x,l,v,s,b,p,r,c) )
    {
      ostringstream os;
      os << "The object *" << x_name
         << "* does not have the right size.\n"
         << "Dimensions should be:"
         << " " << l 
         << " " << v 
         << " " << s 
         << " " << b 
         << " " << p 
         << " " << r 
         << " " << c 
         << ",\nbut they are:         "
         << " " << x.nlibraries() 
         << " " << x.nvitrines()  
         << " " << x.nshelves()   
         << " " << x.nbooks()     
         << " " << x.npages()     
         << " " << x.nrows()      
         << " " << x.ncols()      
         << ".";
      throw runtime_error( os.str() );
    }
}






/*===========================================================================
  === Functions for Agendas
  ===========================================================================*/

//! chk_not_empty
/*! 
    Checks that an agenda is not empty.

    The function gives an error message if the agenda is empty.

    \param    x_name   The name of the agenda.
    \param    x        A variable of type Agenda.

    \author Patrick Eriksson 
    \date   2002-08-20
*/
void chk_not_empty( 
        const String&      x_name,
        const Agenda&      x ) 
{
  if( x.nelem() == 0 )
    {
      ostringstream os;
      os << "The agenda *" << x_name << "* is empty.\nIt is not allowed \n"
         << "that an agenda that is actually used to be empty.\n"
         << "Empty agendas are only created of methods setting dummy values \n"
         << "to variables.";
      throw runtime_error( os.str() );
    }
}







/*===========================================================================
  === Functions for interpolation grids
  ===========================================================================*/

//! Check interpolation grids
/*!
 This function checks if old and new grid for an interpolation are
 ok. If not, it throws a detailed runtime error message. This is
 intended for workspace method input variable checking. If the original grid does
 not have to cover the whole new grid. The returned ing_min and ing_max give
 the positions in the new grid of the first values that are outside the old grid.
 This is only allowed if the boundary value in the input data is 0.
 
 \param[out] ing_min             Index in the new grid with first value covered
                                 by the old grid.
 \param[out] ing_max             Index in the new grid with last value covered
                                 by the old grid.
 \param[in]  which_interpolation A string describing the interpolation for
                                 which the grids are intended. 
 \param[in]  old_grid            The original grid.
 \param[in]  new_grid            The new grid.
 \param[in]  data                The data for the interpolation.
 \param[in]  order               Interpolation order. (Default value is 1.)
 \param[in]  extpolfac           The extrapolation fraction. See gridpos function
                                 for details. Has a default value, which is
                                 consistent with gridpos.  
 
 \author Oliver Lemke (based on chk_interpolation_grids by Stefan)
 \date   2012-03-28
 */
void chk_interpolation_grids_loose(Index&          ing_min,
                                   Index&          ing_max,
                                   const String&   which_interpolation,
                                   ConstVectorView old_grid,
                                   ConstVectorView new_grid,
                                   ConstVectorView data,
                                   const Index     order,
                                   const Numeric&  extpolfac )
{
  const Index n_old = old_grid.nelem();
  
  ostringstream os;
  os << "There is a problem with the grids for the\n"
  << "following interpolation: " << which_interpolation << ".\n";
  
  // Old grid must have at least order+1 elements:
  if (n_old < order+1)
  {
    os << "The original grid must have at least " << order+1 << " elements.";
    throw runtime_error( os.str() );
  }
  
  // Decide whether we have an ascending or descending grid:
  const bool ascending = ( old_grid[0] <= old_grid[1] );
  
  // Minimum and maximum allowed value from old grid. (Will include
  // extrapolation tolerance.)
  Numeric og_min, og_max;
  
  ing_min = 0;
  ing_max = new_grid.nelem()-1;
  if (ascending)  
  {
    // Old grid must be strictly increasing (no duplicate values.)
    if ( !is_increasing(old_grid) )
    {
      os << "The original grid must be strictly sorted\n"
      << "(no duplicate values). Yours is:\n"
      << old_grid << ".";
      throw runtime_error( os.str() );
    }
    
    // Limits of extrapolation. 
    og_min = old_grid[0] - 
    extpolfac * ( old_grid[1] - old_grid[0] );
    og_max = old_grid[n_old-1] + 
    extpolfac * ( old_grid[n_old-1] - old_grid[n_old-2] );
  }
  else
  {
    // Old grid must be strictly decreasing (no duplicate values.)
    if ( !is_decreasing(old_grid) )
    {
      os << "The original grid must be strictly sorted\n"
      << "(no duplicate values). Yours is:\n"
      << old_grid << ".";
      throw runtime_error( os.str() );
    }
    
    // The max is now the first point, the min the last point!
    // I think the sign is right here...
    og_max = old_grid[0] - 
    extpolfac * ( old_grid[1] - old_grid[0] );
    og_min = old_grid[n_old-1] + 
    extpolfac * ( old_grid[n_old-1] - old_grid[n_old-2] );
  }
  
  // Min and max of new grid:
  const Numeric ng_min = min(new_grid);
  const Numeric ng_max = max(new_grid);
  
  // If new grid is not inside old grid, determine the indexes of the range
  // that is.
  
  const Index iog_min = ascending?old_grid.nelem()-1:0;
  const Index iog_max = ascending?0:old_grid.nelem()-1;
  
  if (ng_min < og_min)
  {
    while (ing_max > 0 && new_grid[ing_max] < old_grid[iog_max])
      ing_max--;
  }
  
  if (ng_max > og_max)
  {
    while (ing_min < new_grid.nelem()-1 && new_grid[ing_min] > old_grid[iog_min])
      ing_min++;
  }
  
  if (ing_min > 0 && data[iog_min] != 0)
  {
    os << "\nThe new grid is not fully inside the original grid.\n"
    << "This is allowed if the corresponding boundary value of Raw VMR is 0.\n"
    << "Boundary value: " << data[iog_min];
    throw runtime_error(os.str());
  }
  
  if (ing_max < new_grid.nelem()-1 && data[iog_max] != 0)
  {
    os << "\nThe new grid is not fully inside the original grid.\n"
    << "This is allowed if the corresponding boundary value of Raw VMR is 0.\n"
    << "Boundary value: " << data[iog_max];
    throw runtime_error(os.str());
  }
  
  // If we get here, than everything should be fine.
}


//! Check interpolation grids
/*!
  This function checks if old and new grid for an interpolation are
  ok. If not, it throws a detailed runtime error message. This is
  intended for workspace method input variable checking. 
  
  \param[in] which_interpolation A string describing the interpolation for
                                 which the grids are intended. 
  \param[in] old_grid            The original grid.
  \param[in] new_grid            The new grid.
  \param[in] order               Interpolation order. (Default value is 1.)
  \param[in] extpolfac           The extrapolation fraction. See gridpos function
                                 for details. Has a default value, which is
                                 consistent with gridpos.  
  
  \author Stefan Buehler
  \date   2008-11-24 
*/
void chk_interpolation_grids(const String&   which_interpolation,
                             ConstVectorView old_grid,
                             ConstVectorView new_grid,
                             const Index     order,
                             const Numeric&  extpolfac )
{
  const Index n_old = old_grid.nelem();

  ostringstream os;
  os << "There is a problem with the grids for the\n"
     << "following interpolation: " << which_interpolation << ".\n";

  // Old grid must have at least order+1 elements:
  if (n_old < order+1)
    {
      os << "The original grid must have at least " << order+1 << " elements.";
      throw runtime_error( os.str() );
    }
  
  // Decide whether we have an ascending or descending grid:
  const bool ascending = ( old_grid[0] <= old_grid[1] );

  // Minimum and maximum allowed value from old grid. (Will include
  // extrapolation tolerance.)
  Numeric og_min, og_max;

  if (ascending)  
    {
      // Old grid must be strictly increasing (no duplicate values.)
      if ( !is_increasing(old_grid) )
        {
          os << "The original grid must be strictly sorted\n"
             << "(no duplicate values). Yours is:\n"
             << old_grid << ".";
          throw runtime_error( os.str() );
        }

      // Limits of extrapolation. 
      og_min = old_grid[0] - 
               extpolfac * ( old_grid[1] - old_grid[0] );
      og_max = old_grid[n_old-1] + 
               extpolfac * ( old_grid[n_old-1] - old_grid[n_old-2] );
    }
  else
    {
      // Old grid must be strictly decreasing (no duplicate values.)
      if ( !is_decreasing(old_grid) )
        {
          os << "The original grid must be strictly sorted\n"
             << "(no duplicate values). Yours is:\n"
             << old_grid << ".";
          throw runtime_error( os.str() );
        }

      // The max is now the first point, the min the last point!
      // I think the sign is right here...
      og_max = old_grid[0] - 
               extpolfac * ( old_grid[1] - old_grid[0] );
      og_min = old_grid[n_old-1] + 
               extpolfac * ( old_grid[n_old-1] - old_grid[n_old-2] );
    }
  
  // Min and max of new grid:
  const Numeric ng_min = min(new_grid);
  const Numeric ng_max = max(new_grid);

  // New grid must be inside old grid (plus extpolfac).
  // (Values right on the edge (ng_min==og_min) are still allowed.)

  if (ng_min < og_min)
    {
      os << "The minimum of the new grid must be inside\n"
         << "the original grid. (We allow a bit of extrapolation,\n"
         << "but not so much).\n"
         << "Minimum of original grid:           " << min(old_grid) << "\n"
         << "Minimum allowed value for new grid: " << og_min << "\n"
         << "Actual minimum of new grid:         " << ng_min;
      throw runtime_error( os.str() );
    }

  if (ng_max > og_max)
    {
      os << "The maximum of the new grid must be inside\n"
         << "the original grid. (We allow a bit of extrapolation,\n"
         << "but not so much).\n"
         << "Maximum of original grid:           " << max(old_grid) << "\n"
         << "Maximum allowed value for new grid: " << og_max << "\n"
         << "Actual maximum of new grid:         " << ng_max;
      throw runtime_error( os.str() );
    }

  // If we get here, than everything should be fine.
}


//! Check interpolation grids
/*!
  This function checks if old and new grid for an interpolation are
  ok. If not, it throws a detailed runtime error message. This is
  intended for workspace method input variable checking. 
  
  This is for the special case that the new grid is just a single
  Numeric, instead of a Vector. ("Red" interpolation.)
  It just calles the other more general chk_interpolation_grids
  function for which both grid arguments are vectors.

  \param[in] which_interpolation A string describing the interpolation for
                                 which the grids are intended. 
  \param[in] old_grid            The original grid.
  \param[in] new_grid            The new grid.
  \param[in] order               Interpolation order. (Default value is 1.)
  \param[in] extpolfac           The extrapolation fraction. See gridpos function
                                 for details. Has a default value, which is
                                 consistent with gridpos.  
  
  \author Stefan Buehler
  \date   2008-11-24 
*/
void chk_interpolation_grids(const String&   which_interpolation,
                             ConstVectorView old_grid,
                             const Numeric&  new_grid,
                             const Index     order,
                             const Numeric&  extpolfac )
{
  const Vector v(1, new_grid);
  chk_interpolation_grids(which_interpolation,
                          old_grid,
                          v,
                          order,
                          extpolfac );
}





/*===========================================================================
  === Functions related to atmospheric and surface grids and fields.
  ===========================================================================*/

//! chk_atm_grids 
/*! 
    Checks if the atmospheric grids and the specified atmospheric 
    dimensionality match, and if the grids are ordered correctly.

    The function gives an error message if this is not the case.

    \param    dim          The atmospheric dimensionality.
    \param    p_grid       The pressure grid.
    \param    lat_grid     The latitude grid.
    \param    lon_grid     The longitude grid.

    \author Patrick Eriksson 
    \date   2002-04-15
*/
void chk_atm_grids( 
        const Index&      dim,
        ConstVectorView   p_grid,
        ConstVectorView   lat_grid,
        ConstVectorView   lon_grid )
{
  // p_grid
  if( p_grid.nelem() < 2 )
    throw runtime_error( "The length of *p_grid* must be >= 2." );
  chk_if_decreasing( "p_grid", p_grid );

  // lat_grid
  if( dim == 1 )
    {
      if( lat_grid.nelem() > 0 )
        throw runtime_error("For dim=1, the length of *lat_grid* must be 0.");
    }
  else
    {
      if( lat_grid.nelem() < 2 )
        throw runtime_error(
                         "For dim>1, the length of *lat_grid* must be >= 2.");
      chk_if_increasing( "lat_grid", lat_grid );
    }

  // lon_grid
  if( dim < 3 )
    { 
      if( lon_grid.nelem() > 0 )
        throw runtime_error("For dim<3, the length of *lon_grid* must be 0.");
    }
  else
    {
      if( lon_grid.nelem() < 2 )
        throw runtime_error(
                         "For dim=3, the length of *lon_grid* must be >= 2.");
      chk_if_increasing( "lon_grid", lon_grid );
    }

  // Check that latitude and longitude grids are inside OK ranges for 3D
  if( dim == 3 )
    {
      if( lat_grid[0] < -90 )
        throw runtime_error( 
                  "The latitude grid cannot extend below -90 degrees for 3D" );
      if( lat_grid[lat_grid.nelem() - 1] > 90 )
        throw runtime_error( 
                  "The latitude grid cannot extend above 90 degrees for 3D" );
      if( lon_grid[0] < -360 )
        throw runtime_error( 
                "No longitude (in lon_grid) can be below -360 degrees." );
      if( lon_grid[lon_grid.nelem() - 1] > 360 )
        throw runtime_error( 
                "No longitude (in lon_grid) can be above 360 degrees." );
      if( lon_grid[lon_grid.nelem() - 1]-lon_grid[0] > 360 )
        throw runtime_error( 
         "The longitude grid is not allowed to cover more than 360 degrees." );
    }
}



//! chk_atm_field (simple fields)
/*! 
    Checks if an atmospheric field matches the dimensionality and the grids.

    The function gives an error message if this is not the case.

    \param    x_name       The name of the atmospheric field.
    \param    x            A variable holding an atmospheric field.
    \param    dim          The atmospheric dimensionality.
    \param    p_grid       The pressure grid.
    \param    lat_grid     The latitude grid.
    \param    lon_grid     The longitude grid.

    \author Patrick Eriksson 
    \date   2002-04-15
*/
void chk_atm_field( 
        const String&     x_name,
        ConstTensor3View  x, 
        const Index&      dim,
        ConstVectorView   p_grid,
        ConstVectorView   lat_grid,
        ConstVectorView   lon_grid )
{
  // It is assumed that grids OK-ed through chk_atm_grids
  Index npages=p_grid.nelem(), nrows=1, ncols=1;
  if( dim > 1 )
    nrows = lat_grid.nelem();
  if( dim > 2 )
    ncols = lon_grid.nelem();
  if( x.ncols()!=ncols || x.nrows()!=nrows || x.npages()!=npages ) 
    {
      ostringstream os;
      os << "The atmospheric field *" << x_name <<  "* has wrong size.\n"
         << "Expected size is " << npages << " x " << nrows << " x " 
         << ncols << ", while actual size is " << x.npages() << " x " 
         << x.nrows() << " x " << x.ncols() << ".";
      throw runtime_error( os.str() );
    }
  // Special 3D checks:
  if( dim == 3  )
    {
      // If all lons are covered, check if cyclic
      if( (lon_grid[ncols-1]-lon_grid[0]) == 360 )
        {
          const Index ic = ncols-1;
          for( Index ip=0; ip<npages; ip++ )
            {
              for( Index ir=0; ir<nrows; ir++ )
                {
                  if( fabs(x(ip,ir,ic)-x(ip,ir,0)) > 0 )
                    {
                      ostringstream os;
                      os << "The variable *" << x_name <<  "* covers 360 "
                         << "degrees in the longitude direction, but the field "
                         << "seems to deviate between first and last longitude "
                         << "point. The field must be \"cyclic\".";
                      throw runtime_error( os.str() );
                    }
                }
            }
        }

      // No variation at the South pole!
      if( lat_grid[0] == -90 )
        {
          for( Index ip=0; ip<npages; ip++ )
            {
              for( Index ic=1; ic<ncols; ic++ )
                {
                  if( fabs(x(ip,0,ic)-x(ip,0,ic-1)) > 0 )
                    {
                      ostringstream os;
                      os << "The variable *" << x_name <<  "* covers the South "
                         << "pole. The data corresponding to the pole can not "
                         << "vary with longitude, but this appears to be the "
                         << "case.";
                      throw runtime_error( os.str() );
                    }
                }
            }
        }
      // No variation at the North pole!
      if( lat_grid[nrows-1] == 90 )
        {
          const Index ir = nrows-1;
          for( Index ip=0; ip<npages; ip++ )
            {
              for( Index ic=1; ic<ncols; ic++ )
                {
                  if( fabs(x(ip,ir,ic)-x(ip,ir,ic-1)) > 0 )
                    {
                      ostringstream os;
                      os << "The variable *" << x_name <<  "* covers the North "
                         << "pole. The data corresponding to the pole can not "
                         << "vary with longitude, but this appears to be the "
                         << "case.";
                      throw runtime_error( os.str() );
                    }
                }
            }
        }
    }
}



//! chk_atm_field (fields with one more dimension)
/*! 
    Checks if an atmospheric field matches the dimensionality and the
    grids. This is the version for fields like vmr_field, which are a
    Tensor4, not a Tensor3. (First dimension is the gas species.)

    The function gives an error message if this is not the case.

    \param    x_name       The name of the atmospheric field.
    \param    x            A variable holding an atmospheric field.
    \param    dim          The atmospheric dimensionality.
    \param    nspecies     Number of species.
    \param    p_grid       The pressure grid.
    \param    lat_grid     The latitude grid.
    \param    lon_grid     The longitude grid.

    \author Stefan Buehler, cloned from Patrick Eriksson 
    \date   2002-12-20
*/
void chk_atm_field( 
        const String&   x_name,
        ConstTensor4View  x, 
        const Index&    dim,
        const Index&    nspecies,
        ConstVectorView p_grid,
        ConstVectorView lat_grid,
        ConstVectorView lon_grid )
{
  const Index nbooks=nspecies;
  // 
  if( nbooks == 0 )
    {
      if( x.nbooks() )
        {
          ostringstream os;
          os << "The atmospheric field *" << x_name <<  "* should be empty.\n";
          throw runtime_error( os.str() );
        }
      else
        { return; }
    }


  Index npages=p_grid.nelem(), nrows=1, ncols=1;
  if( dim > 1 )
    nrows = lat_grid.nelem();
  if( dim > 2 )
    ncols = lon_grid.nelem();

  if( x.ncols()!=ncols || x.nrows()!=nrows || x.npages()!=npages ||
      x.nbooks()!=nbooks ) 
    {
      ostringstream os;
      os << "The atmospheric field *" << x_name <<  "* has wrong size.\n"
         << "Expected size is "
         << nbooks << " x " << npages << " x "
         << nrows << " x " << ncols << ",\n"
         << "while actual size is "
         << x.nbooks() << " x " << x.npages() << " x "
         << x.nrows() << " x " << x.ncols() << ".";
      throw runtime_error( os.str() );
    }
  // Special 3D checks:
  if( dim == 3  )
    {
      // If all lons are covered, check if cyclic
      if( (lon_grid[ncols-1]-lon_grid[0]) == 360 )
        {
          const Index ic = ncols-1;
          for( Index is=0; is<nspecies; is++ )
            {
          for( Index ip=0; ip<npages; ip++ )
            {
              for( Index ir=0; ir<nrows; ir++ )
                {
                  if( fabs(x(is,ip,ir,ic)-x(is,ip,ir,0)) > 0 )
                    {
                      ostringstream os;
                      os << "The variable *" << x_name <<  "* covers 360 "
                         << "degrees in the longitude direction, but at least "
                         << "one field seems to deviate between first and last "
                         << "longitude point. The field must be \"cyclic\". "
                         << "This was found for field with index " 
                         << is <<" (0-based).";
                      throw runtime_error( os.str() );
                    }
                }
            }
            }
        }
      // No variation at the South pole!
      if( lat_grid[0] == -90 )
        {
          for( Index is=0; is<nspecies; is++ )
            {
          for( Index ip=0; ip<npages; ip++ )
            {
              for( Index ic=1; ic<ncols; ic++ )
                {
                  if( fabs(x(is,ip,0,ic)-x(is,ip,0,ic-1)) > 0 )
                    {
                      ostringstream os;
                      os << "The variable *" << x_name <<  "* covers the South "
                         << "pole. The data corresponding to the pole can not "
                         << "vary with longitude, but this appears to be the "
                         << "case. This was found for field with index " 
                         << is <<" (0-based).";
                      throw runtime_error( os.str() );
                    }
                }
            }
            }
        }
      // No variation at the North pole!
      if( lat_grid[nrows-1] == 90 )
        {
          const Index ir = nrows-1;
          for( Index is=0; is<nspecies; is++ )
            {
          for( Index ip=0; ip<npages; ip++ )
            {
              for( Index ic=1; ic<ncols; ic++ )
                {
                  if( fabs(x(is,ip,ir,ic)-x(is,ip,ir,ic-1)) > 0 )
                    {
                      ostringstream os;
                      os << "The variable *" << x_name <<  "* covers the North "
                         << "pole. The data corresponding to the pole can not "
                         << "vary with longitude, but this appears to be the "
                         << "case. This was found for field with index " 
                         << is <<" (0-based).";
                      throw runtime_error( os.str() );
                    }
                }
            }
            }
        }
    }
}



//! chk_latlon_true
/*! 
    Checks that *lat_true* and *lon_true* have the correct size for 1D and 2D
    cases (they are not used for 3D). The functions returns also the lat and
    lon grids to apply for geopositioning data.

    \param   lat              Set to lat_true for 1D and 2D, lat_grid for 3D
    \param   lon              Set to lon_true for 1D and 2D, lon_grid for 3D
    \param   atmosphere_dim   As the WSV with the same name
    \param   lat_grid         As the WSV with the same name
    \param   lon_grid         As the WSV with the same name
    \param   lat_true         As the WSV with the same name
    \param   lon_true         As the WSV with the same name

    \author Patrick Eriksson 
    \date   2012-03-19
*/
void chk_latlon_true(
        Vector&      lat,
        Vector&      lon,  
   const Index&      atmosphere_dim,
   ConstVectorView   lat_grid,
   ConstVectorView   lon_grid,
   ConstVectorView   lat_true,
   ConstVectorView   lon_true )
{
  if( atmosphere_dim == 1 )
    {
      if( lat_true.nelem()!=1  ||  lon_true.nelem()!=1 )
        { 
          throw runtime_error( "For 1D, the method requires that *lat_true* "
                                              "and *lon_true* have length 1." );
        }
      lat = lat_true;
      lon = lon_true;
    }
  //
  else if( atmosphere_dim == 2 ) 
    {
      if( lat_true.nelem() != lat_grid.nelem()   ||  
          lon_true.nelem() != lon_grid.nelem() )
        { 
          throw runtime_error( "For 2D, the method requires that *lat_true* "
                         "and *lon_true* have the same length as *lat_grid*." );
        }
      lat = lat_true;   
      lon = lon_true;
    }
  //
  else
    {
      lat = lat_grid;
      lon = lon_grid;
    }
}



//! chk_atm_surface
/*! 
    Checks if a surface-type variable matches the dimensionality and the grids.

    The function gives an error message if this is not the case.

    \param    x_name       The name of the surface-type variable.
    \param    x            The variable holding the surface data.
    \param    dim          The atmospheric dimensionality.
    \param    lat_grid     The latitude grid.
    \param    lon_grid     The longitude grid.

    \author Patrick Eriksson 
    \date   2002-04-15
*/
void chk_atm_surface( 
        const String&     x_name,
        const Matrix&     x, 
        const Index&      dim,
        ConstVectorView   lat_grid,
        ConstVectorView   lon_grid )
{
  Index ncols=1, nrows=1;
  if( dim > 1 )
    nrows = lat_grid.nelem();
  if( dim > 2 )
    ncols = lon_grid.nelem();
  if( x.ncols()!=ncols || x.nrows()!=nrows ) 
    {
      ostringstream os;
      os << "The surface variable *" << x_name <<  "* has wrong size.\n"
         << "Expected size is " << nrows << " x " << ncols << ","
         << " while actual size is " << x.nrows() << " x " << x.ncols() << ".";
      throw runtime_error( os.str() );
    }
  // If all lons are covered, check if cyclic
  if( dim == 3  &&  (lon_grid[ncols-1]-lon_grid[0]) == 360 )
    {
      const Index ic = ncols-1;
      for( Index ir=0; ir<nrows; ir++ )
        {
          if( fabs(x(ir,ic)-x(ir,0)) > 0 )
            {
              ostringstream os;
              os << "The variable *" << x_name <<  "* covers 360 "
                 << "degrees in the longitude direction, but the data "
                 << "seems to deviate between first and last longitude "
                 << "point. The surface must be \"cyclic\".";
              throw runtime_error( os.str() );
            }
        }
    }
}



//! chk_pnd_field_raw_only_in_cloudbox
/*! 
    Checks whether the pnd_field is zero outside the cloudbox.
    This is of a higher level than chk_pnd_data because it does
    not require any filename and because it works on all pnd_field_raw
    rather than just one element. Otherwise, it is mostly a new
    implementation of the same functionality.

    \param    dim                The atmospheric dimensionality.
    \param    pnd_field_raw      All pnd_field_raw data.
    \param    p_grid             Pressure grid.
    \param    lat_grid           Latitude grid.
    \param    lon_grid           Longitude grid.
    \param    cloudbox_limits    The edges of the cloudbox.

    \author Gerrit Holl
    \date   2011-03-24
*/
void chk_pnd_field_raw_only_in_cloudbox(
        const Index&                 dim,
        const ArrayOfGriddedField3&  pnd_field_raw,  
        ConstVectorView              p_grid,
        ConstVectorView              lat_grid,
        ConstVectorView              lon_grid,
        const ArrayOfIndex&          cloudbox_limits )
{
    Numeric p, lat, lon, v;
    Index n, p_i, lat_i, lon_i;
    // For any non-zero point, verify we're outside the cloudbox
    for (n=0; n < pnd_field_raw.nelem(); n++) {
        for (p_i=0; p_i < pnd_field_raw[n].data.npages(); p_i++) {
            for (lat_i=0; lat_i < pnd_field_raw[n].data.nrows(); lat_i++) {
                for (lon_i=0; lon_i < pnd_field_raw[n].data.ncols(); lon_i++) {
                    v = pnd_field_raw[n].data(p_i, lat_i, lon_i);
                    if (v != 0) {
                        // Verify pressure is between cloudbox limits
                        p = pnd_field_raw[n].get_numeric_grid(GFIELD3_P_GRID)[p_i];
                        if (!((p <= p_grid[cloudbox_limits[0]]) &
                              (p >= p_grid[cloudbox_limits[1]]))) {
                            ostringstream os;
                            os << "Found non-zero pnd outside cloudbox. "
                               << "Cloudbox extends from p="
                               << p_grid[cloudbox_limits[0]]
                               << " Pa to p="
                               << p_grid[cloudbox_limits[1]]
                               << " Pa, but found pnd=" << v
                               << "/m³ at p=" << p << " Pa.";
                            throw runtime_error(os.str());
                        }
                        // Verify latitude is too
                        if (dim > 1) {
                            lat = pnd_field_raw[n].get_numeric_grid(GFIELD3_LAT_GRID)[lat_i];
                            if (!((lat >= lat_grid[cloudbox_limits[2]]) &
                                  (lat <= lat_grid[cloudbox_limits[3]]))) {
                                ostringstream os;
                                os << "Found non-zero pnd outside cloudbox. "
                                   << "Cloudbox extends from lat="
                                   << lat_grid[cloudbox_limits[2]]
                                   << "° to lat="
                                   << lat_grid[cloudbox_limits[3]]
                                   << "°, but found pnd=" << v
                                   << "/m³ at lat=" << lat << "°.";
                                throw runtime_error(os.str());
                            }
                        }
                        // Etc. for longitude
                        if (dim > 2) {
                            lon = pnd_field_raw[n].get_numeric_grid(GFIELD3_LON_GRID)[lon_i];
                            if (!((lon >= lon_grid[cloudbox_limits[4]]) &
                                  (lon <= lon_grid[cloudbox_limits[5]]))) {
                                ostringstream os;
                                os << "Found non-zero pnd outside cloudbox. "
                                   << "Cloudbox extends from lon="
                                   << lon_grid[cloudbox_limits[4]]
                                   << "° to lat="
                                   << lon_grid[cloudbox_limits[5]]
                                   << "°, but found pnd=" << v
                                   << "/m³ at lon=" << lon << "°.";
                                throw runtime_error(os.str());
                            }
                        }
                    }
                }
            }
        }
    }
}





/*===========================================================================
  === Functions related to sensor variables.
  ===========================================================================*/

//! chk_rte_pos
/*! 
    Performs all needed checks of rte_pos and rte_pos2.

    The function gives an error message if this is not the case.

    \param    atmosphere_dim   As the WSV with the same name.
    \param    rte_pos          As WSV rte_pos or rte_pos2.
    \param    is_rte_pos2      True if rte_pos actually is rte_pos2.

    \author Patrick Eriksson 
    \date   2012-03-26
*/
void chk_rte_pos( 
        const Index&      atmosphere_dim,
        ConstVectorView   rte_pos,
        const Index&      is_rte_pos2 )

{  
  String vname = "*rte_pos*";
  if( is_rte_pos2 )
    { vname = "*rte_pos2*"; }

  if( atmosphere_dim == 1 )
    {
      if( !is_rte_pos2 )
        {
          if( rte_pos.nelem() != 1 )
            {
              ostringstream os;
              os << "For 1D, " << vname << " must have length 1.";
              throw runtime_error(os.str());
            }
        }
      else
        {
          if( rte_pos.nelem() != 2 )
            {
              ostringstream os;
              os << "For 1D, " << vname << " must have length 2.";
              throw runtime_error(os.str());
            }
          if( rte_pos[1] < -90  ||  rte_pos[1] > 90 )
            {
              ostringstream os;
              os << "For 1D, the latitude in " << vname << " must be in the "
                 << "range [-180,180].";
              throw runtime_error(os.str());
            }
        }
    }
  else if( atmosphere_dim == 2 )
    { 
      if( rte_pos.nelem() != 2 )
        {
          ostringstream os;
          os << "For 2D, " << vname << " must have length 2.";
          throw runtime_error(os.str());
        }
    }
  else
    {
      if( rte_pos.nelem() != 3 )
        {
          ostringstream os;
          os << "For 3D, " << vname << " must have length 3.";
          throw runtime_error(os.str());
        }
      if( rte_pos[1] < -90  ||  rte_pos[1] > 90 )
        {
          ostringstream os;
          os << "The (3D) latitude in " << vname << " must be in the "
             << "range [-90,90].";
          throw runtime_error(os.str());
        }
      if( rte_pos[2] < -360  ||  rte_pos[2] > 360 )
        {
          ostringstream os;
          os << "The longitude in " << vname << " must be in the "
             << "range [-360,360].";
          throw runtime_error(os.str());
        } 
    }
}



//! chk_rte_los
/*! 
    Performs all needed checks of rte_los

    The function gives an error message if this is not the case.

    \param    atmosphere_dim   As the WSV with the same name.
    \param    rte_los          As the WSV with the same name.

    \author Patrick Eriksson 
    \date   2012-03-26
*/
void chk_rte_los( 
        const Index&      atmosphere_dim,
        ConstVectorView   rte_los )

{  
  if( atmosphere_dim == 1 )
    {
      if( rte_los.nelem() != 1 )
        { throw runtime_error( "For 1D, *rte_los* must have length 1." ); }
      if( rte_los[0] < 0  ||  rte_los[0] > 180 )
        { throw runtime_error( "For 1D, the zenith angle of *rte_los* must "
                               "be in the range [0,180]." ); }
    }
  else if( atmosphere_dim == 2 )
    { 
      if( rte_los.nelem() != 1 )
        { throw runtime_error( "For 2D, *rte_los* must have length 1." ); }
      if( rte_los[0] < -180  ||  rte_los[0] > 180 )
        { throw runtime_error( "For 2D, the zenith angle of *rte_los* must "
                               "be in the range [-180,180]." ); }
    }
  else
    {
      if( rte_los.nelem() != 2 )
        { throw runtime_error( "For 3D, *rte_los* must have length 2." ); }
      if( rte_los[0] < 0  ||  rte_los[0] > 180 )
        { throw runtime_error( "For 3D, the zenith angle of *rte_los* must "
                               "be in the range [0,180]." ); }
      if( rte_los[1] < -180  ||  rte_los[1] > 180 )
        { throw runtime_error( "For 3D, the azimuth angle of *rte_los* must "
                               "be in the range [-180,180]." ); }
    }
}




