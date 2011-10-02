#!/usr/bin/env python


def launch_keeper(options, i):
    pass


def launch_monitor(options):
    pass


def launch_server(options):
    from socket import gethostname
    from subprocess import Popen
    from time import strftime

    # Some helpful vars.
    log_name = '%s-%s' % (strftime('%Y%m%d%H%M'), gethostname())

    # The server options need to be exactly what goes to the server.
    server_options = []

    if options.log_keepaway:
        server_options.append(['keepaway_logging', 1]);
        server_options.append(['keepaway_log_dir', options.log_dir]);
        server_options.append(['keepaway_log_fixed', 1]);
        server_options.append(['keepaway_log_fixed_name', log_name]);

    if options.log_game:
        server_options.append(['game_log_dir', options.log_dir]);
        server_options.append(['game_log_fixed', 1]);
        server_options.append(['game_log_fixed_name', log_name]);
    else:
        server_options.append(['game_logging', 0]);

    server_options.append(['port', options.port]);

    if options.log_text:
        server_options.append(['text_log_dir', options.log_dir]);
        server_options.append(['text_log_fixed', 1]);
        server_options.append(['text_log_fixed_name', log_name]);
    else:
        server_options.append(['text_logging', 0]);

    if not options.restricted_vision:
        server_options.append(['visible_angle', 360])
    server_options = [
        'server::%s=%s' % tuple(option) for option in server_options]

    # TODO Locate rcssserver executable reliably.
    command = ['../rcssserver/src/rcssserver'] + server_options
    print command
    Popen(command)
    # TODO Launch.


def launch_taker(options, i):
    pass


def main():
    options = parse_options()
    print options
    # Kick off server.
    launch_server(options)
    # Then players.
    for i in xrange(options.keeper_count):
        launch_keeper(options, i)
    for i in xrange(options.taker_count):
        launch_taker(options, i)
    # Then monitor.
    if options.monitor:
        launch_monitor(options)


def parse_options():
    from optparse import OptionParser
    parser = OptionParser()
    default_port = 5800
    default_size = 20
    parser.add_option(
        '--coach-port', type = 'int', default = default_port + 1,
        help = "Offline trainer port.")
    parser.add_option(
        '--field-length', type = 'int', default = default_size,
        help = "Playing field x-axis size.")
    parser.add_option(
        '--field-width', type = 'int', default = default_size,
        help = "Playing field y-axis size.")
    parser.add_option(
        '--game-start', type = 'int', default = 8,
        help = "Game start delay time.")
    parser.add_option(
        '--keeper-count', type = 'int', default = 3,
        help = "Number of keepers.")
    parser.add_option(
        '--log-dir', default = "./logs",
        help = "Directory for storing log files.")
    parser.add_option(
        '--log-game', action = 'store_true', default = False,
        help = "Save rcg log file.")
    parser.add_option(
        '--log-text', action = 'store_true', default = False,
        help = "Save rcl (message/command) log file.")
    parser.add_option(
        '--monitor', action = 'store_true', default = False,
        help = "Launch the monitor to watch the play.")
    parser.add_option(
        '--no-log-keepaway', action = 'store_false', default = True,
        dest = 'log_keepaway', 
        help = "Do not save kwy log file.")
    parser.add_option(
        '--online-coach-port', type = 'int', default = default_port + 2,
        help = "Online coach port.")
    parser.add_option(
        '--port', type = 'int', default = default_port,
        help = "RCSS server port.")
    parser.add_option(
        '--restricted-vision', action = 'store_true', default = False,
        help = "Restrict player vision to less than 360 degrees.")
    parser.add_option(
        '--synch-mode', action = 'store_true', default = False,
        help = "Speed up with synchronous mode.")
    parser.add_option(
        '--taker-count', type = 'int', default = 2,
        help = "Number of takers.")
    options = parser.parse_args()[0]
    return options


#rcssserver
#server::half_time=-1
#server::forbid_kick_off_offside=0
#server::use_offside=0
#server::stamina_inc_max=3500
#server::synch_offset=80
#server::keepaway=1
#server::keepaway_log_dir=/home/tom/Workspace/keepaway/logs
#server::keepaway_log_fixed=1
#server::keepaway_log_fixed_name=201110011426-tom-mini9
#server::game_log_dir=/home/tom/Workspace/keepaway/logs
#server::game_log_compression=0
#server::game_log_version=5
#server::game_log_fixed=1
#server::game_log_fixed_name=201110011426-tom-mini9
#server::text_log_dir=/home/tom/Workspace/keepaway/logs
#server::text_log_compression=0
#server::text_log_fixed=1
#server::text_log_fixed_name=201110011426-tom-mini9
#server::visible_angle=360
#server::coach=0


if __name__ == '__main__':
    main()
