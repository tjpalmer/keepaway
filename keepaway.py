#!/usr/bin/env python


def launch_player(player_type, options):
    """Launcher for both keepers and takers."""
    from itertools import chain
    from subprocess import Popen

    # Build up the options for the player process.
    # TODO $klog_opts $kdraw_opts $kweight_opts
    player_options = dict(
        e = int(getattr(options, player_type + '_learn')),
        f = getattr(options, player_type + '_output'),
        j = options.taker_count,
        k = options.keeper_count,
        p = options.port,
        q = getattr(options, player_type + '_policy'),
        t = player_type + 's', # Pluralize for team name. TODO Really?
        x = options.stop_after,
        y = options.start_learning_after,
        w = getattr(options, player_type + '_input'))

    # Change the dict to a sorted list of args.
    player_options = player_options.items()
    player_options.sort()
    player_options = [
        ('-%s' % option[0], str(option[1])) for option in player_options]
    player_options = list(chain(*player_options))

    # Build keepaway_player command, and fork it off.
    # TODO Locate rcssserver executable reliably.
    command = ['./player/keepaway_player'] + player_options
    # print command
    # print " ".join(command)
    Popen(command)


def launch_monitor(options):
    from subprocess import Popen
    # I can't find any way to zoom automatically on startup. Oh well.
    monitor_options = [('server-port', options.port)]
    monitor_options = [
        '--%s=%s' % option for option in monitor_options]
    command = ['../rcssmonitor_qt4/src/rcssmonitor'] + monitor_options
    # print command
    # print " ".join(command)
    Popen(command)


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
    
    # Either keepaway or trainer mode. Field size.
    server_options += [('keepaway', int(not options.coach))]
    server_options += [('keepaway_start', options.game_start)]
    server_options += [
        ('keepaway_length', options.field_length),
        ('keepaway_width', options.field_width)]

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
    # print command
    # print " ".join(command)
    Popen(command)

    # Wait until the server is ready.
    wait_for_server(options.port)


def main():
    from time import sleep
    options = parse_options()
    # print options
    # Kick off server.
    launch_server(options)
    # Then keepers.
    for i in xrange(options.keeper_count):
        launch_player('keeper', options)
    # Then takers, after sleeping to make sure keepers are team 0.
    # TODO Watch for players instead of sleeping?
    # TODO If so, also use 'dispstart' command to start play once all on.
    sleep(1)
    for i in xrange(options.taker_count):
        launch_player('taker', options)
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
        '--keeper-input',
        help = "Input (file) name for keeper policy agent.")
    parser.add_option(
        '--keeper-learn', action = 'store_true', default = False,
        help = "Turn learning on for keepers.")
    parser.add_option(
        '--keeper-output',
        help = "Output (file) name for keeper policy agent.")
    parser.add_option(
        '--keeper-policy',
        # Allow --keeper-policy=ext=./whatever.so, so remove choices.
        # TODO Nicer syntax for extensions?
        #type = 'choice', choices = ['hand', 'hold', 'learned', 'rand'],
        default = 'rand',
        help = "The policy for the keepers to follow.")
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
        '--start-learning-after', type = 'int', default = -1,
        help = "Start learning after the given number of episodes.")
    parser.add_option(
        '--stop-after', type = 'int', default = -1,
        help = "Stop play after the given number of episodes.")
    parser.add_option(
        '--synch-mode', action = 'store_true', default = False,
        help = "Speed up with synchronous mode.")
    parser.add_option(
        '--taker-count', type = 'int', default = 2,
        help = "Number of takers.")
    parser.add_option(
        '--taker-input',
        help = "Input (file) name for taker policy agent.")
    parser.add_option(
        '--taker-learn', action = 'store_true', default = False,
        help = "Turn learning on for takers.")
    parser.add_option(
        '--taker-output',
        help = "Output (file) name for taker policy agent.")
    parser.add_option(
        '--taker-policy', default = 'hand',
        # Allow --keeper-policy=ext=./whatever.so, so remove choices.
        # TODO Nicer syntax for extensions?
        #type = 'choice', choices = ['hand', 'learned'],
        help = "The policy for the takers to follow.")
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
