using ScoreService.Repositories;
using ScoreService.Services;

var builder = WebApplication.CreateBuilder(args);

// Configure for app service deployment: https://github.com/Azure/app-service-linux-docs/blob/master/HowTo/gRPC/use_gRPC_with_dotnet.md
builder.WebHost.ConfigureKestrel(options => {
	options.ListenAnyIP(8080, listenOptions => {
		listenOptions.Protocols = Microsoft.AspNetCore.Server.Kestrel.Core.HttpProtocols.Http2;
	});
	options.ListenAnyIP(8585, listenOptions => {
		listenOptions.Protocols = Microsoft.AspNetCore.Server.Kestrel.Core.HttpProtocols.Http2;
		//listenOptions.UseHttps(); // This is needed for local debugging of HTTPS
	});
});

// Add services to the container.
builder.Services.AddGrpc();
builder.Services.AddSingleton<IUserScoreRepository, UserScoreFileSystemRepository>();

var app = builder.Build();

// Configure the HTTP request pipeline.
app.MapGrpcService<GreeterService>();
app.MapGrpcService<ScoreService.Services.ScoreService>();
app.MapGet("/", () => "Communication with gRPC endpoints must be made through a gRPC client. To learn how to create a client, visit: https://go.microsoft.com/fwlink/?linkid=2086909");

app.Run();
