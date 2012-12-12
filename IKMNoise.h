/** 
* @file IKMNoise.h
* @author Erik Rodner, Alexander Freytag
* @brief Noise matrix (for model regularization) as an implicit kernel matrix (Interface)
* @date 02/14/2012

*/
#ifndef _NICE_IKMNOISEINCLUDE
#define _NICE_IKMNOISEINCLUDE

#include <vector>
#include "ImplicitKernelMatrix.h"

namespace NICE {

 /** 
 * @class IKMNoise
 * @brief Noise matrix (for model regularization) as an implicit kernel matrix
 * @author Erik Rodner, Alexander Freytag
 */

class IKMNoise : public ImplicitKernelMatrix
{

  protected:
    Vector labels;

    uint size;

    double noise;

    bool optimizeNoise;

    uint np;
    uint nn;
    
    /** give some debug outputs. There is not set function so far... */
    bool verbose;
  
  public:

    IKMNoise();
    
    IKMNoise( uint size, double noise, bool optimizeNoise );
    
    IKMNoise( const Vector & labels, double noise, bool optimizeNoise );
      
    virtual ~IKMNoise();

    virtual void getDiagonalElements ( Vector & diagonalElements ) const;
    virtual void getFirstDiagonalElement ( double & diagonalElement ) const;
    virtual uint getNumParameters() const;
    
    virtual void getParameters(Vector & parameters) const;
    virtual void setParameters(const Vector & parameters);
    virtual bool outOfBounds(const Vector & parameters) const;

    virtual Vector getParameterLowerBounds() const;
    virtual Vector getParameterUpperBounds() const;

    /** multiply with a vector: A*x = y */
    virtual void multiply (NICE::Vector & y, const NICE::Vector & x) const;

    /** get the number of rows in A */
    virtual uint rows () const;

    /** get the number of columns in A */
    virtual uint cols () const;
    
    virtual double approxFrobNorm() const;
    virtual void setApproximationScheme(const int & _approxScheme) {};
    
    /** Persistent interface */
    virtual void restore ( std::istream & is, int format = 0 );
    virtual void store ( std::ostream & os, int format = 0 ) const; 
    virtual void clear () {};
    
    void addExample(const NICE::SparseVector & x, const NICE::Vector & binLabels);

};

}

#endif