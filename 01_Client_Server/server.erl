-module(server).
-export([start/0]).

% Address server implemented in erlang, it manages simple address space and handles requests
% 


loop()->
	receive
		{insert, Name}->
			io:format("recv insert"),
			ets:insert(address_space, Name),
		loop();
		{delete, Name}->
			io:format("recv delete"),

		loop();
		{lookup, Name}->
			io:format("recv lookup"),
			ets:lookup(address_space, Name),
		loop();

		stop->
			io:format("recv stop"),
	
		loop()

	end.

start()->
	ets:new(address_space, [bag]),
	Pid = spawn(fun()->loop() end),
	Pid !{insert, first}.

