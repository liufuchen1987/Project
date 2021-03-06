/* soapClient.cpp
   Generated by gSOAP 2.8.15 from ..\gsoap_input\MyWsSvr_ns2.h

Copyright(C) 2000-2013, Robert van Engelen, Genivia Inc. All Rights Reserved.
The generated code is released under ONE of the following licenses:
GPL or Genivia's license for commercial use.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
*/

#if defined(__BORLANDC__)
#pragma option push -w-8060
#pragma option push -w-8004
#endif
#include "soapH.h"

SOAP_SOURCE_STAMP("@(#) soapClient.cpp ver 2.8.15 2014-12-01 07:15:30 GMT")


SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns2__Login(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::wstring szPara, std::wstring &result)
{	struct ns2__Login soap_tmp_ns2__Login;
	struct ns2__LoginResponse *soap_tmp_ns2__LoginResponse;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost";
	soap->encodingStyle = "";
	soap_tmp_ns2__Login.szPara = szPara;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns2__Login(soap, &soap_tmp_ns2__Login);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns2__Login(soap, &soap_tmp_ns2__Login, "ns2:Login", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_url(soap, soap_endpoint, NULL), soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns2__Login(soap, &soap_tmp_ns2__Login, "ns2:Login", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&result)
		return soap_closesock(soap);
	soap_default_std__wstring(soap, &result);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_tmp_ns2__LoginResponse = soap_get_ns2__LoginResponse(soap, NULL, "", "");
	if (!soap_tmp_ns2__LoginResponse || soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	result = soap_tmp_ns2__LoginResponse->result;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns2__QueryData(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::wstring szPara, std::wstring &result_info)
{	struct ns2__QueryData soap_tmp_ns2__QueryData;
	struct ns2__QueryDataResponse *soap_tmp_ns2__QueryDataResponse;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost";
	soap->encodingStyle = "";
	soap_tmp_ns2__QueryData.szPara = szPara;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns2__QueryData(soap, &soap_tmp_ns2__QueryData);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns2__QueryData(soap, &soap_tmp_ns2__QueryData, "ns2:QueryData", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_url(soap, soap_endpoint, NULL), soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns2__QueryData(soap, &soap_tmp_ns2__QueryData, "ns2:QueryData", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&result_info)
		return soap_closesock(soap);
	soap_default_std__wstring(soap, &result_info);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_tmp_ns2__QueryDataResponse = soap_get_ns2__QueryDataResponse(soap, NULL, "", "");
	if (!soap_tmp_ns2__QueryDataResponse || soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	result_info = soap_tmp_ns2__QueryDataResponse->result_info;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns2__UpdateData(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::wstring szPara, std::wstring &result_info)
{	struct ns2__UpdateData soap_tmp_ns2__UpdateData;
	struct ns2__UpdateDataResponse *soap_tmp_ns2__UpdateDataResponse;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost";
	soap->encodingStyle = "";
	soap_tmp_ns2__UpdateData.szPara = szPara;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns2__UpdateData(soap, &soap_tmp_ns2__UpdateData);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns2__UpdateData(soap, &soap_tmp_ns2__UpdateData, "ns2:UpdateData", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_url(soap, soap_endpoint, NULL), soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns2__UpdateData(soap, &soap_tmp_ns2__UpdateData, "ns2:UpdateData", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&result_info)
		return soap_closesock(soap);
	soap_default_std__wstring(soap, &result_info);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_tmp_ns2__UpdateDataResponse = soap_get_ns2__UpdateDataResponse(soap, NULL, "", "");
	if (!soap_tmp_ns2__UpdateDataResponse || soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	result_info = soap_tmp_ns2__UpdateDataResponse->result_info;
	return soap_closesock(soap);
}

#if defined(__BORLANDC__)
#pragma option pop
#pragma option pop
#endif

/* End of soapClient.cpp */
