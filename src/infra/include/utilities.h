#pragma once

#include <map>
#include <string>

#define IN
#define OUT
#define INOUT

enum ErrorCode
{
	UTILS_ERROR_CODE_SUCCESS = 0,
	UTILS_ERROR_CODE_GENERAL_FAUILRE,
    UTILS_ERROR_CODE_NO_INTERFACE
};

class Result
{
public:
	explicit Result(const enum ErrorCode& errorCode)
		: m_errorCode(errorCode)
	{

	}

	bool IsSuccess() const
	{
		return (m_errorCode == ErrorCode::UTILS_ERROR_CODE_SUCCESS);
	}

	ErrorCode GetErrorCode() const
	{
		return m_errorCode;
	}

    std::string GetErrorCodeMessage() const
    {
        auto it = errorCodeMap.find(m_errorCode);
        if (it != errorCodeMap.end())
        {
            return it->second;
        } 
        else
        {
            // Handle unknown error code (optional)
            return "Unknown Error Code";
        }
    }

private:
	ErrorCode m_errorCode;
    
    std::map<ErrorCode, std::string> errorCodeMap = 
    {
        {ErrorCode::UTILS_ERROR_CODE_SUCCESS, "Success"},
        {ErrorCode::UTILS_ERROR_CODE_GENERAL_FAUILRE, "General Failure"},
        {ErrorCode::UTILS_ERROR_CODE_NO_INTERFACE, "No interface found in the VRF"}
    };
};




