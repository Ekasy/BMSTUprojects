#include <iostream>
#include <string>

class cls_OutOfRangeException : public std::exception {
	std::string m_Msg;

public:
	cls_OutOfRangeException(int p_FirstInd, int p_Size1)
	{
		m_Msg.assign("ERROR: Vector out of range.\nIndex [" + std::to_string(p_FirstInd + 1) +
			"] is outside the vector[" + std::to_string(p_Size1) + "]\n");
	}
	const char * what() const {
		return m_Msg.c_str();
	}
};


class cls_IncompatibleDimException : public std::exception {
	std::string m_Msg;

public:
	cls_IncompatibleDimException(int p_FirstDim, int p_SecondDim)
	{
		m_Msg.assign("ERROR: Incompatible dimmensions of operands.\nFirst dim = " +
			std::to_string(p_FirstDim) + ", second dim = " + std::to_string(p_SecondDim) + "\n");
	}
	const char * what() const {
		return m_Msg.c_str();
	}
};