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

    uint size;

    double noise;

    bool optimizeNoise;

   
    /** give some debug outputs. There is not set function so far... */
    bool verbose;
  
  public:

    IKMNoise();
    
    IKMNoise( uint size, double noise, bool optimizeNoise );
    
      
    virtual ~IKMNoise();

    virtual void getDiagonalElements ( NICE::Vector & diagonalElements ) const;
    virtual void getFirstDiagonalElement ( double & diagonalElement ) const;
    virtual uint getNumParameters() const;
    
    virtual void getParameters( NICE::Vector & parameters) const;
    virtual void setParameters(const NICE::Vector & parameters);
    virtual bool outOfBounds(const NICE::Vector & parameters) const;

    virtual NICE::Vector getParameterLowerBounds() const;
    virtual NICE::Vector getParameterUpperBounds() const;

    /** multiply with a vector: A*x = y */
    virtual void multiply (NICE::Vector & y, const NICE::Vector & x) const;

    /** get the number of rows in A */
    virtual uint rows () const;

    /** get the number of columns in A */
    virtual uint cols () const;
    
    virtual double approxFrobNorm() const;
    virtual void setApproximationScheme(const int & _approxScheme) {};
    
    ///////////////////// INTERFACE PERSISTENT /////////////////////
    // interface specific methods for store and restore
    ///////////////////// INTERFACE PERSISTENT /////////////////////
    virtual void restore ( std::istream & is, int format = 0 );
    virtual void store ( std::ostream & os, int format = 0 ) const; 
    virtual void clear () {};
    
    ///////////////////// INTERFACE ONLINE LEARNABLE /////////////////////
    // interface specific methods for incremental extensions
    ///////////////////// INTERFACE ONLINE LEARNABLE /////////////////////    
    
    virtual void addExample( const NICE::SparseVector * example, 
			     const double & label, 
			     const bool & performOptimizationAfterIncrement = true
			   );
			   
    virtual void addMultipleExamples( const std::vector< const NICE::SparseVector * > & newExamples,
				      const NICE::Vector & newLabels,
				      const bool & performOptimizationAfterIncrement = true
				    );        
    

};

}

#endif
