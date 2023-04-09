#include <userver/utest/using_namespace_userver.hpp>

#include <userver/components/minimal_server_component_list.hpp>
#include <userver/server/handlers/http_handler_base.hpp>
#include <userver/testsuite/testsuite_support.hpp>
#include <userver/clients/dns/component.hpp>
#include <userver/utils/daemon_run.hpp>

#include <userver/storages/postgres/cluster.hpp>
#include <userver/storages/postgres/component.hpp>

static constexpr char KeyValueDataBase[] = "key-value-database";

class TestHandler final : public server::handlers::HttpHandlerBase
{
public:
    TestHandler(const components::ComponentConfig &config,
                const components::ComponentContext &ctx)
        : server::handlers::HttpHandlerBase{config, ctx},
          pgCluster_{ctx.FindComponent<components::Postgres>(KeyValueDataBase)
                         .GetCluster()}
    {
        static constexpr char createTable[] = "CREATE TABLE IF NOT EXISTS key_value_table ("
                                              "key VARCHAR PRIMARY KEY,"
                                              "value VARCHAR"
                                              ")";

        pgCluster_->Execute(storages::postgres::ClusterHostType::kMaster, createTable);
    }

    std::string HandleRequestThrow(const server::http::HttpRequest &req,
                                   server::request::RequestContext &ctx) const final
    {
        switch (req.GetMethod())
        {
        case server::http::HttpMethod::kGet:
            return getValue(req, ctx);

        case server::http::HttpMethod::kPost:
            return postValue(req, ctx);

        case server::http::HttpMethod::kDelete:
            return deleteValue(req, ctx);

        default:
            throw server::handlers::ClientError{server::handlers::ExternalBody{
                fmt::format("Unsupported method {0}", req.GetMethod())}};
        }
    }

public:
    static constexpr std::string_view kName = "handler-key-value";

private:
    std::string getValue(const server::http::HttpRequest &req,
                         server::request::RequestContext &ctx) const
    {
        return {};
    }

    std::string postValue(const server::http::HttpRequest &req,
                          server::request::RequestContext &ctx) const
    {
        return {};
    }

    std::string deleteValue(const server::http::HttpRequest &req,
                            server::request::RequestContext &ctx) const
    {
        return {};
    }

private:
    storages::postgres::ClusterPtr pgCluster_;
};

int main(int argc, char const *argv[])
{
    auto component_list = components::MinimalServerComponentList();

    component_list.Append<TestHandler>();
    component_list.Append<components::Postgres>(KeyValueDataBase);
    component_list.Append<clients::dns::Component>();
    component_list.Append<components::TestsuiteSupport>();

    return utils::DaemonMain(argc, argv, component_list);
}
