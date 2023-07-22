project('dbus_example', 
        'c', 
        default_options : ['warning_level=3'])

systemd_dep = dependency('libsystemd')

executable('client', 
            'client.c', 
            dependencies : systemd_dep)

executable('server', 
            'server.c', 
            dependencies : systemd_dep)
