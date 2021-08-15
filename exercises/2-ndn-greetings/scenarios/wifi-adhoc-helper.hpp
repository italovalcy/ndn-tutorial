#include "ns3/ndnSIM/model/ndn-l3-protocol.hpp"
#include "ns3/ndnSIM/NFD/daemon/face/generic-link-service.hpp"
#include "model/ndn-net-device-transport.hpp"

namespace ns3 {
std::string
constructFaceUri(Ptr<NetDevice> netDevice)
{
  std::string uri = "netdev://";
  Address address = netDevice->GetAddress();
  if (Mac48Address::IsMatchingType(address)) {
    uri += "[" + boost::lexical_cast<std::string>(Mac48Address::ConvertFrom(address)) + "]";
  }

  return uri;
}

std::shared_ptr<ndn::Face>
FixLinkTypeAdhocCb(Ptr<Node> node, Ptr<ndn::L3Protocol> ndn,
                                           Ptr<NetDevice> netDevice)
{
  // Create an ndnSIM-specific transport instance
  ::nfd::face::GenericLinkService::Options opts;
  opts.allowFragmentation = true;
  opts.allowReassembly = true;
  opts.allowCongestionMarking = true;

  auto linkService = std::make_unique<::nfd::face::GenericLinkService>(opts);

  auto transport = std::make_unique<ndn::NetDeviceTransport>(node, netDevice,
                                                   constructFaceUri(netDevice),
                                                   "netdev://[ff:ff:ff:ff:ff:ff]", /* remote face */
                                                   ::ndn::nfd::FACE_SCOPE_NON_LOCAL,
                                                   ::ndn::nfd::FACE_PERSISTENCY_PERSISTENT,
                                                   ::ndn::nfd::LINK_TYPE_AD_HOC);

  auto face = std::make_shared<ndn::Face>(std::move(linkService), std::move(transport));
  face->setMetric(1);

  ndn->addFace(face);
  std::cout << "Node " << node->GetId() << ": added Face id=" << face->getId()
                                                   << " uri=" << face->getLocalUri() << std::endl;
  return face;
}
} // namespace ns3 
