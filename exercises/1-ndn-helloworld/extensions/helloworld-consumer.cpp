/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "helloworld-consumer.hpp"

#include <limits>
#include <cmath>
#include <boost/algorithm/string.hpp> 
#include <algorithm>

#define MYLOG_COMPONENT "ndn.HelloworldConsumer"
#include "mylog-helper.hpp"

namespace ndn {
namespace greetings {

HelloworldConsumer::HelloworldConsumer(Name prefix)
  : m_scheduler(m_face.getIoService())
  , m_prefix(prefix)
  , m_seq(0)
  , m_rengine(rdevice_())
  , m_rand_nonce(0, std::numeric_limits<int>::max())
{
}

void HelloworldConsumer::Start() {
  m_scheduler.schedule(time::seconds(1), [this] { SendInterest(); });
}

void HelloworldConsumer::Stop() {
}

void HelloworldConsumer::run() {
  m_face.processEvents();
}

void HelloworldConsumer::cleanup() {
}

void
HelloworldConsumer::SendInterest() {
  Name name = Name(m_prefix);
  name.appendNumber(m_seq++);
  MYLOG_INFO("Sending Interest " << name);

  Interest interest = Interest();
  interest.setNonce(m_rand_nonce(m_rengine));
  interest.setName(name);
  interest.setCanBePrefix(false);
  interest.setInterestLifetime(time::seconds(1));

  m_face.expressInterest(interest,
    std::bind(&NdnGreetings::OnHelloworldContent, this, _1, _2),
    std::bind(&NdnGreetings::OnHelloworldNack, this, _1, _2),
    std::bind(&NdnGreetings::OnHelloworldTimedOut, this, _1));

  m_scheduler.schedule(time::seconds(1), [this] { SendInterest(); });
}

void HelloworldConsumer::OnHelloworldContent(const ndn::Interest& interest, const ndn::Data& data) {
  MYLOG_DEBUG("Received Helloworld " << data.getName());
}

void HelloworldConsumer::OnHelloworldTimedOut(const ndn::Interest& interest) {
  MYLOG_DEBUG("Interest timed out for Name: " << interest.getName());
}

void HelloworldConsumer::OnHelloworldNack(const ndn::Interest& interest, const ndn::lp::Nack& nack) {
  MYLOG_DEBUG("Received Nack with reason: " << nack.getReason());
}

} // namespace helloworld
} // namespace ndn
