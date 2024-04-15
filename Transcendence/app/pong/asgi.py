"""
ASGI config for pong project.

It exposes the ASGI callable as a module-level variable named ``application``.

For more information on this file, see
https://docs.djangoproject.com/en/5.0/howto/deployment/asgi/
"""

import os

from django.core.asgi import get_asgi_application
from channels.routing import ProtocolTypeRouter, URLRouter, ChannelNameRouter
from channels.auth import AuthMiddlewareStack
import frontend.routing
import frontend.consumers as consumers


os.environ.setdefault('DJANGO_SETTINGS_MODULE', 'pong.settings')

# application = get_asgi_application()
application = ProtocolTypeRouter({
    'http': get_asgi_application(),
    'websocket': AuthMiddlewareStack(
        URLRouter(frontend.routing.websocket_urlpatterns)
    ),
    "channel": ChannelNameRouter({
        "redis": consumers.GameConsumer,
    }),
})
