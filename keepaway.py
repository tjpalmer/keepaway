#!/usr/bin/env python


def launch_keeper(options, i):
    # ./keepaway_player -p 5800 -k 3 -j 2 -x -1 -y -1 -t keepers -e 0 -q rand
    pass


def launch_monitor(options):
    pass


def launch_server(options):
    from socket import gethostname
    from subprocess import Popen
    from time import strftime

    # Some helpful vars.
    log_name = '%s-%s' % (strftime('%Y%m%d%H%M'), gethostname())

    # Build up the server arguments. Alphabetical order follows.
    server_options = []

    # Coach/trainer mode.
    server_options += [
        ('coach', int(options.coach)),
        ('coach_port', options.coach_port)]

    # Hardcoded settings for keepaway play.
    server_options += [('forbid_kick_off_offside', 0)]
    server_options += [('half_time', -1)]
    
    # Either keepaway or trainer mode.
    server_options += [('keepaway', int(not options.coach))]
    server_options += [('keepaway_start', options.game_start)]

    if options.log_keepaway:
        server_options += [
            ('keepaway_logging', 1),
            ('keepaway_log_dir', options.log_dir),
            ('keepaway_log_fixed', 1),
            ('keepaway_log_fixed_name', log_name)];

    if options.log_game:
        server_options += [
            # TODO Parameterize compression?
            ('game_log_compression', 0),
            ('game_log_dir', options.log_dir),
            ('game_log_fixed', 1),
            ('game_log_fixed_name', log_name),
            # TODO Parameterize the version number?
            ('game_log_version', 5)];
    else:
        server_options += [('game_logging', 0)];

    # Server and online coach ports.
    server_options += [
        ('olcoach_port', options.online_coach_port),
        ('port', options.port)];

    # Hardcoded stamina inc. This was hardcoded in keepaway.sh.
    # TODO What's the effect, and what's default?
    # TODO Any changes to other new defaults in rcssserver to retain benchmarks?
    server_options += [('stamina_inc_max', 3500)];

    # Synch mode. TODO What's default, and does synch offset matter when not
    # TODO in synch mode?
    server_options += [
        ('synch_mode', int(options.synch_mode)),
        # Synch offset 80 was hardcoded in keepaway.sh.
        ('synch_offset', 80)]

    if options.log_text:
        server_options += [
            # TODO Parameterize compression?
            ('text_log_compression', 0),
            ('text_log_dir', options.log_dir),
            ('text_log_fixed', 1),
            ('text_log_fixed_name', log_name)];
    else:
        server_options += [('text_logging', 0)];

    # More hardcoded settings for keepaway play.
    server_options += [('use_offside', 0)]

    # Vision limits. TODO What's the normal default?
    if not options.restricted_vision:
        server_options += [('visible_angle', 360)]

    server_options = [
        'server::%s=%s' % option for option in server_options]

    # Build rcssserver command, and fork it off.
    # TODO Locate rcssserver executable reliably.
    command = ['../rcssserver/src/rcssserver'] + server_options
    print command
    Popen(command)

    # Wait until the server is ready.
    wait_for_server(options.port)


def launch_taker(options, i):
    # ./keepaway_player -p 5800 -k 3 -j 2 -x -1 -y -1 -t takers -e 0 -q hand
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
        '--coach', action = 'store_true', default = False,
        help = "Use trainer instead of server referee.")
    parser.add_option(
        # TODO More options are needed before coach/trainer is ready.
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


def wait_for_server(port):
    """Impersonate a monitor to see if the server is running yet."""
    from socket import AF_INET, SOCK_DGRAM, socket
    from time import sleep
    sock = socket(AF_INET, SOCK_DGRAM)
    try:
        sock.setblocking(False)
        sock.bind(('', 0))
        # Loop until successful.
        while True:
            # Delay a bit between attempts, so we don't bother the server nor
            # the user console.
            sleep(0.25)
            try:
                sock.sendto(
                    '(dispinit version 4)', ('127.0.0.1', port))
                # Sample rcssclient uses buffer size 8192.
                # TODO Do I care to validate these? data, sender =
                sock.recvfrom(8192)
                sock.sendto('(dispbye)', ('127.0.0.1', port))
                # Good to go.
                break
            except:
                # TODO Check to make sure it's the right kind of error?
                pass
    finally:
        sock.close()


if __name__ == '__main__':
    main()
