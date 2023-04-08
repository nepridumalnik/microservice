#include <userver/utest/using_namespace_userver.hpp>

#include <userver/components/minimal_server_component_list.hpp>
#include <userver/server/handlers/http_handler_base.hpp>
#include <userver/utils/daemon_run.hpp>

class TestHandler final : public server::handlers::HttpHandlerBase
{
public:
    using HttpHandlerBase::HttpHandlerBase;

    std::string HandleRequestThrow(const server::http::HttpRequest &req,
                                   server::request::RequestContext &context) const override
    {
        static const std::string respond = "Hello world!";
        return respond;
    }

public:
    static constexpr std::string_view kName = "handler-hello-sample";
};

int main(int argc, char *argv[])
{
    const auto component_list =
        components::MinimalServerComponentList().Append<TestHandler>();
    return utils::DaemonMain(argc, argv, component_list);
}
