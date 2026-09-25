// SPDX-FileCopyrightText: Copyright 2024 shadPS4 Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#include <common/assert.h>
#include "core/libraries/kernel/kernel.h"
#include "net.h"
#include "net_error.h"
#include "sockets.h"

namespace Libraries::Net {

P2PSocket::P2PSocket(int domain, int type, int protocol) : Socket(domain, type, protocol) {
    m_transport = std::make_shared<PosixSocket>(AF_INET, SOCK_DGRAM, protocol);

    if (!m_transport->IsValid()) {
        LOG_ERROR(Lib_Net, "Failed to create native UDP transport for P2P socket");
        m_transport.reset();
    } else {
        LOG_INFO(Lib_Net, "Created native UDP transport for P2P socket");
    }
}

int P2PSocket::Close() {
    std::scoped_lock lock(m_mutex);

    if (!m_transport) {
        return 0;
    }

    const int result = m_transport->Close();
    m_transport.reset();

    return result;
}

int P2PSocket::Shutdown(int how) {
    LOG_ERROR(Lib_Net, "(STUBBED) called");
    return 0;
}

int P2PSocket::SetSocketOptions(int level, int optname, const void* optval, u32 optlen) {
    if (!m_transport) {
        *Libraries::Kernel::__Error() = ORBIS_NET_EBADF;
        return -1;
    }

    return m_transport->SetSocketOptions(level, optname, optval, optlen);
}

int P2PSocket::GetSocketOptions(int level, int optname, void* optval, u32* optlen) {
    if (!m_transport) {
        *Libraries::Kernel::__Error() = ORBIS_NET_EBADF;
        return -1;
    }

    return m_transport->GetSocketOptions(level, optname, optval, optlen);
}

int P2PSocket::Bind(const OrbisNetSockaddr* addr, u32 addrlen) {
    if (!m_transport) {
        *Libraries::Kernel::__Error() = ORBIS_NET_EBADF;
        return -1;
    }

    return m_transport->Bind(addr, addrlen);
}

int P2PSocket::Listen(int backlog) {
    if (!m_transport) {
        *Libraries::Kernel::__Error() = ORBIS_NET_EBADF;
        return -1;
    }

    return m_transport->Listen(backlog);
}

int P2PSocket::SendMessage(const OrbisNetMsghdr* msg, int flags) {
    if (!m_transport) {
        *Libraries::Kernel::__Error() = ORBIS_NET_EBADF;
        return -1;
    }

    return m_transport->SendMessage(msg, flags);
}

int P2PSocket::SendPacket(const void* msg, u32 len, int flags, const OrbisNetSockaddr* to,
                          u32 tolen) {
    if (!m_transport) {
        *Libraries::Kernel::__Error() = ORBIS_NET_EBADF;
        return -1;
    }

    return m_transport->SendPacket(msg, len, flags, to, tolen);
}

int P2PSocket::ReceiveMessage(OrbisNetMsghdr* msg, int flags) {
    if (!m_transport) {
        *Libraries::Kernel::__Error() = ORBIS_NET_EBADF;
        return -1;
    }

    return m_transport->ReceiveMessage(msg, flags);
}

int P2PSocket::ReceivePacket(void* buf, u32 len, int flags, OrbisNetSockaddr* from, u32* fromlen) {
    if (!m_transport) {
        *Libraries::Kernel::__Error() = ORBIS_NET_EBADF;
        return -1;
    }

    return m_transport->ReceivePacket(buf, len, flags, from, fromlen);
}

SocketPtr P2PSocket::Accept(OrbisNetSockaddr* addr, u32* addrlen) {
    if (!m_transport) {
        *Libraries::Kernel::__Error() = ORBIS_NET_EBADF;
        return nullptr;
    }

    return m_transport->Accept(addr, addrlen);
}

int P2PSocket::Connect(const OrbisNetSockaddr* addr, u32 namelen) {
    if (!m_transport) {
        *Libraries::Kernel::__Error() = ORBIS_NET_EBADF;
        return -1;
    }

    return m_transport->Connect(addr, namelen);
}

int P2PSocket::GetSocketAddress(OrbisNetSockaddr* name, u32* namelen) {
    if (!m_transport) {
        *Libraries::Kernel::__Error() = ORBIS_NET_EBADF;
        return -1;
    }

    return m_transport->GetSocketAddress(name, namelen);
}

int P2PSocket::GetPeerName(OrbisNetSockaddr* addr, u32* namelen) {
    if (!m_transport) {
        *Libraries::Kernel::__Error() = ORBIS_NET_EBADF;
        return -1;
    }

    return m_transport->GetPeerName(addr, namelen);
}

int P2PSocket::fstat(Libraries::Kernel::OrbisKernelStat* stat) {
    if (!m_transport) {
        *Libraries::Kernel::__Error() = ORBIS_NET_EBADF;
        return -1;
    }

    return m_transport->fstat(stat);
}

std::optional<net_socket> P2PSocket::Native() {
    if (!m_transport) {
        return {};
    }

    return m_transport->Native();
}

u16 GetP2PConfiguredPort() {
    return 0;
}

u32 GetP2PAdvertisedAddr() {
    return 0;
}

bool EnsureP2PTransport() {
    return true;
}

bool P2PTransportIsReady() {
    return true;
}

int P2PSignalingSendTo(const void* data, u32 len, u32 dest_addr, u16 dest_port) {
    *Libraries::Kernel::__Error() = ORBIS_NET_EAGAIN;
    return -1;
}

int P2PSignalingRecvFrom(void* buf, u32 len, u32* from_addr, u16* from_port) {
    *Libraries::Kernel::__Error() = ORBIS_NET_EAGAIN;
    return -1;
}

int P2PControlSendTo(const void* data, u32 len, u32 dest_addr, u16 dest_port) {
    *Libraries::Kernel::__Error() = ORBIS_NET_EAGAIN;
    return -1;
}

int P2PControlRecvFrom(void* buf, u32 len, u32* from_addr, u16* from_port) {
    *Libraries::Kernel::__Error() = ORBIS_NET_EAGAIN;
    return -1;
}

int P2PMatching2SendTo(const void* data, u32 len, u32 dest_addr, u16 dest_port) {
    *Libraries::Kernel::__Error() = ORBIS_NET_EAGAIN;
    return -1;
}

int P2PMatching2RecvFrom(void* buf, u32 len, u32* from_addr, u16* from_port) {
    *Libraries::Kernel::__Error() = ORBIS_NET_EAGAIN;
    return -1;
}

} // namespace Libraries::Net
