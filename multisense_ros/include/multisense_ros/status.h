/**
 * @file status.h
 *
 * Copyright 2020
 * Carnegie Robotics, LLC
 * 4501 Hatfield Street, Pittsburgh, PA 15201
 * http://www.carnegierobotics.com
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Carnegie Robotics, LLC nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL CARNEGIE ROBOTICS, LLC BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 **/

#ifndef MULTISENSE_ROS_STATUS_H
#define MULTISENSE_ROS_STATUS_H

#include <rclcpp/rclcpp.hpp>

#include <MultiSense/MultiSenseChannel.hh>

#include <multisense_msgs/msg/device_status.hpp>
#include <multisense_msgs/msg/ptp_status.hpp>

namespace multisense_ros {

class Status : public rclcpp::Node
{
public:

    Status(const std::string& node_name, crl::multisense::Channel* driver);
    ~Status();

private:
    static constexpr char STATUS_TOPIC[] = "status";
    static constexpr char PTP_STATUS_TOPIC[] = "ptp_status";

    //
    // CRL sensor API

    crl::multisense::Channel* driver_;

    //
    // Device Status publisher

    rclcpp::Publisher<multisense_msgs::msg::DeviceStatus>::SharedPtr status_pub_;

    //
    // PTP Status publisher

    rclcpp::Publisher<multisense_msgs::msg::PtpStatus>::SharedPtr ptp_status_pub_;

    //
    // A timer to query our device status at a fixed rate

    rclcpp::TimerBase::SharedPtr timer_;

    //
    // The callback used to query the device status in the timer routine

    void queryStatus();

    //
    // A flag which determines if we should query the PTP status info

    bool ptp_status_supported_ = false;

};

}

#endif
