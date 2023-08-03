project('dbus_example', 
        'c', 
        default_options : ['warning_level=3'])

systemd_dep = dependency('libsystemd')

executable('client', 
            'client/main.c', 
            dependencies : systemd_dep)

executable('server', 
            'server/main.c', 
            dependencies : systemd_dep)

executable('simple', 
            'simple/main.c', 
            dependencies : systemd_dep)