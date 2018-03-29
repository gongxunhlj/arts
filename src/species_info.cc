/* Copyright 2018, Richard Larsson.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2, or (at your option) any
 * later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
 
#include "species_info.h"
#include "wigner_functions.h"
#include "absorption.h"


/*! Returns the lande spin constant
 *  
 *  Data is from these
 *  
 *  H. Christensen, and L. Veseth, On the High-Precision Zeeman Effect in 02 and SO.
 *  Journal of Molecular Spectroscopy 72, 438-444, 1978.
 *  
 *  L. Veseth, Relativistic Corrections to the Zeeman Effect in Diatomic Molecules.
 *  Journal of Molecular Spectroscopy 66, 259-271, 1977.
 *  
 *  The final return is an averaged number that you get from 2*(1 + 0.5*alpha/PI + 
 *  X*(alpha/PI)**2 + ...), where alpha approx 1/137 is the fine-structure constant.
 *  
 *  The default return of this function is from the NIST database
 */
Numeric get_lande_spin_constant(const LineRecord& line) noexcept
{ 
  if     (species_index_from_species_name("O2" ) == line.Species()) return 2.002064; 
  else if(species_index_from_species_name("NO" ) == line.Species()) return 2.00071;  
  else if(species_index_from_species_name("OH" ) == line.Species()) return 2.00089;
  else if(species_index_from_species_name("ClO") == line.Species()) return 2.00072;
  else if(species_index_from_species_name("SO" ) == line.Species()) return 2.002106;
  else return 2.00231930436182;
}


Numeric reduced_dipole(const LineRecord& line)
{
  const static Rational one = Rational(1, 1);
  
  if(species_index_from_species_name("CO2") == line.Species()) {
    const Rational& Jf = line.QuantumNumbers().Lower(QuantumNumberType::J);
    const Rational& Ji = line.QuantumNumbers().Upper(QuantumNumberType::J);
    const Rational& l2f = line.QuantumNumbers().Lower(QuantumNumberType::l2);
    const Rational& l2i = line.QuantumNumbers().Upper(QuantumNumberType::l2);
    const Index sign = (Jf+l2f+1).toIndex()?1:-1;
    const Numeric root = sqrt((2*Jf+1).toNumeric());
    const Numeric w3j_res = wigner3j(Ji,  one,      Jf,
                                     l2i, l2f-l2i, -l2f);
    return Numeric(sign) * root * w3j_res;
  }
  else if(species_index_from_species_name("O2") == line.Species()) { // C++ version of pureHund in module_phsub.F90...
    if(line.QuantumNumbers().Lower(QuantumNumberType::Hund).toIndex() == Index(Hund::CaseA))
      throw std::runtime_error("Hund case a not implemented for O2 reduced dipole");
    const Rational& Nf = line.QuantumNumbers().Lower(QuantumNumberType::N);
    const Rational& Ni = line.QuantumNumbers().Upper(QuantumNumberType::N);
    const Rational& Jf = line.QuantumNumbers().Lower(QuantumNumberType::J);
    const Rational& Ji = line.QuantumNumbers().Upper(QuantumNumberType::J);
    Numeric c;
    if((Nf == Ni+1) and (Jf == Ji+1))
      c = sqrt(Ji.toNumeric());
    else if((Nf == Ni+1) and (Jf == Ji))
      c = -sqrt(Ji.toNumeric() + 1.0);
    else if((Nf == Ni-1) and (Jf == Ji))
      c = -sqrt(Ji.toNumeric());
    else if((Nf == Ni-1) and (Jf == Ji-1))
      c = sqrt(Ji.toNumeric() + 1.0);
    else
      c = 1.0;
    return c / sqrt(((2*Ji+1).toNumeric()));
  }
  else  {
    ostringstream os;
    os << "Failed to get reduced dipole for this line:\n" << line << "\n";
    os << "Is this an attempt to use a new species or are you lacking the required quantum numbers in the line record?\n";
    throw std::runtime_error(os.str());
  }
}


Numeric sign_reduced_dipole(const LineRecord& line)
{
  return Numeric(copysign(Numeric(1.0), reduced_dipole(line)));
}

