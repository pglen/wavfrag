
/* =====[ Fft.h ]========================================== 
                                                                             
   Description:     The daco project, implementation of the Fft.h                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  2/7/2010  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#if !defined CFft_H
#define CFft_H

#pragma warning (disable : 4786)

#include <complex>
#include <vector>
#include <cassert>

typedef std::complex<double> Complex;


class CFft
{

public:

	// Construct it
    CFft (unsigned points, unsigned sampleRate);

	// Hard work
    void    Transform (std::vector<int> const & data);

	// Output: from i = 0 to points-1
    double  GetIntensity (unsigned i) const
		{ 
        assert (i < _points);
        return std::abs (_X[i]) / _sqrtPoints; 
		}

    // return number of points
    unsigned Points () const { return _points; }
	
	// return frequency in Hz of a given point
    int GetFrequency (unsigned point) const
		{
        assert (point < _points);
        long x =_sampleRate * point;
        return x / _points;
		}

    int HzToPoint (int freq) const 
		{ 
        return (long)_points * freq / _sampleRate; 
		}

    int MaxFreq() const { return _sampleRate; }

protected:

	void CFft::Transform2();
	void DataIn (std::vector<int> const & data);
    void PutAt (unsigned i, double val)
	    {
        _X [_aBitRev[i]] = Complex (val);
		}

private:

    unsigned	_points;
    unsigned	_sampleRate;
    unsigned	_logPoints;		// binary log of _points
    double		_sqrtPoints;	// square root of _points

	std::vector<unsigned>				_aBitRev;	// bit reverse vector
	std::vector<Complex>				_X;			// in-place CFft array
	std::vector<std::vector<Complex> >	_W;			// exponentials
	std::vector<double>					_tape;		// recording tape
};

//pragma warning (default : 4786)

#endif
