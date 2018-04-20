-module(server).
-export([start/0]).

% Address server implemented in erlang, it manages simple address space and handles requests
% 


loop()->
	receive
		{insert, Name, Desc}->
			io:format("recv insert~n"),
			ets:insert(proc_table, {Name, Desc}),
		loop();
		{delete, Name}->
			io:format("recv delete~n"),

		loop();
		{lookup, Name}->
			io:format("recv lookup~n"),
			T = ets:lookup(proc_table, Name),
			io:format("~p~n", [T]),
		loop();

		{stop}->
			ets:delete(proc_table),
			io:format("recv stop~n")

		after 1000->
			ets:delete(proc_table),
			io:format("timeout~n")
	end.

run()->
	ets:new(proc_table, [set, named_table]),
	loop().

start()->
	Pid = spawn(fun()->run() end),
	Pid !{insert, apple, first},
	Pid !{insert, orange, second},
	Pid !{insert, bacon, third},

	Pid ! {lookup, bacon}.


