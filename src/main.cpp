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
                const components::ComponentContext &context)
        : server::handlers::HttpHandlerBase{config, context},
          pgCluster_{context.FindComponent<components::Postgres>(KeyValueDataBase)
                         .GetCluster()}
    {
        static constexpr char createTable[] = "CREATE TABLE IF NOT EXISTS key_value_table ("
                                              "key VARCHAR PRIMARY KEY,"
                                              "value VARCHAR"
                                              ")";

        pgCluster_->Execute(storages::postgres::ClusterHostType::kMaster, createTable);
    }

    std::string HandleRequestThrow(const server::http::HttpRequest &req,
                                   server::request::RequestContext &context) const override
    {
        static const std::string respond = "Hello world!";
        return respond;
    }

public:
    static constexpr std::string_view kName = "handler-key-value";

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
