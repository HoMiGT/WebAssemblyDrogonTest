#pragma once
#include <drogon/HttpSimpleController.h>
#include <drogon/HttpResponse.h>
#include <drogon/HttpController.h>
#include <drogon/HttpAppFramework.h>

#define DI( n ) index##n

#define DF( n ) fetch##n

#define INDEX( n ) void DI(n)(const drogon::HttpRequestPtr& req,std::function<void(const drogon::HttpResponsePtr&)>&& callback) const;
#define FETCH( n ) void DF(n)(const drogon::HttpRequestPtr& req,std::function<void(const drogon::HttpResponsePtr&)>&& callback) const;

#define AddController(C, n) \
	class C : public drogon::HttpController<C> { \
	public: \
		METHOD_LIST_BEGIN \
		ADD_METHOD_TO(C::DI(n), "/" #n, drogon::Get); \
		ADD_METHOD_TO(C::DF(n), "/" #n "/wasm", drogon::Get); \
		METHOD_LIST_END \
		INDEX(n) \
		FETCH(n); \
	};

#define AddFunction(C,n,s,w) \
    void C::DI(n)(const drogon::HttpRequestPtr& req, std::function<void(const drogon::HttpResponsePtr&)>&& callback) const {\
        auto resp = drogon::HttpResponse::newHttpResponse();\
        resp->setStatusCode(drogon::k200OK);\
        resp->setContentTypeCode(drogon::CT_TEXT_HTML);\
        resp->setBody(std::move(s));\
        callback(resp);\
    }\
    void C::DF(n)(const drogon::HttpRequestPtr& req, std::function<void(const drogon::HttpResponsePtr&)>&& callback) const\
    {\
        auto resp = drogon::HttpResponse::newHttpResponse();\
        std::ifstream file(w, ios::in | ios::binary);\
        if (!file.is_open()) {\
            resp->setStatusCode(HttpStatusCode::k404NotFound);\
            resp->setBody("File not found.");\
        }\
        else {\
            resp->setStatusCode(HttpStatusCode::k200OK); \
            resp->setContentTypeCode(ContentType::CT_APPLICATION_WASM);\
            std::vector<char> buffer(std::istreambuf_iterator<char>(file), {});\
            std::string contents(buffer.begin(), buffer.end());\
            resp->setBody(contents);\
            file.close();\
        }\
        callback(resp);\
    }


AddController(CHelloWorld,0)

AddController(CModule,1)

AddController(CTestMain,2)

AddController(CSquare,3)

AddController(CReverse,4)

AddController(CFib,5)

AddController(CPair,6)