/*
Navicat MySQL Data Transfer

Source Server         : mysql
Source Server Version : 50722
Source Host           : localhost:3306
Source Database       : hotel

Target Server Type    : MYSQL
Target Server Version : 50722
File Encoding         : 65001

Date: 2021-01-04 09:18:54
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for admin
-- ----------------------------
DROP TABLE IF EXISTS `admin`;
CREATE TABLE `admin` (
  `Aid` varchar(20) NOT NULL,
  `Apassword` varchar(20) NOT NULL,
  PRIMARY KEY (`Aid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of admin
-- ----------------------------
INSERT INTO `admin` VALUES ('admin', 'admin');

-- ----------------------------
-- Table structure for client
-- ----------------------------
DROP TABLE IF EXISTS `client`;
CREATE TABLE `client` (
  `Rno` varchar(20) DEFAULT NULL,
  `Cname` varchar(20) NOT NULL,
  `Cno` varchar(20) NOT NULL,
  `Ctele` varchar(20) DEFAULT NULL,
  `Cday` int(11) DEFAULT NULL,
  `Cin` varchar(20) DEFAULT NULL,
  `Cout` varchar(20) DEFAULT NULL,
  PRIMARY KEY (`Cno`),
  KEY `Rno` (`Rno`),
  CONSTRAINT `Rno` FOREIGN KEY (`Rno`) REFERENCES `room` (`Rno`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of client
-- ----------------------------

-- ----------------------------
-- Table structure for room
-- ----------------------------
DROP TABLE IF EXISTS `room`;
CREATE TABLE `room` (
  `Rno` varchar(20) NOT NULL,
  `Rtype` varchar(20) NOT NULL,
  `Rstate` varchar(20) NOT NULL,
  `Rclean` varchar(20) NOT NULL,
  PRIMARY KEY (`Rno`),
  KEY `Rtype` (`Rtype`),
  CONSTRAINT `Rtype` FOREIGN KEY (`Rtype`) REFERENCES `room_type` (`Rtype`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of room
-- ----------------------------
INSERT INTO `room` VALUES ('D01', '单人间', '空', '否');
INSERT INTO `room` VALUES ('D02', '单人间', '空', '否');
INSERT INTO `room` VALUES ('D03', '单人间', '空', '否');
INSERT INTO `room` VALUES ('D04', '单人间', '空', '否');
INSERT INTO `room` VALUES ('G01', '3D观影房', '空', '否');
INSERT INTO `room` VALUES ('G02', '3D观影房', '空', '否');
INSERT INTO `room` VALUES ('G03', '3D观影房', '空', '否');
INSERT INTO `room` VALUES ('H01', '豪华大床房', '空', '否');
INSERT INTO `room` VALUES ('H02', '豪华大床房', '空', '否');
INSERT INTO `room` VALUES ('H03', '豪华大床房', '空', '否');
INSERT INTO `room` VALUES ('H04', '豪华大床房', '空', '否');
INSERT INTO `room` VALUES ('J01', '精致大床房', '空', '否');
INSERT INTO `room` VALUES ('J02', '精致大床房', '空', '否');
INSERT INTO `room` VALUES ('J03', '精致大床房', '空', '否');
INSERT INTO `room` VALUES ('J04', '精致大床房', '空', '否');
INSERT INTO `room` VALUES ('J05', '精致大床房', '空', '否');
INSERT INTO `room` VALUES ('S01', '双人间', '空', '否');
INSERT INTO `room` VALUES ('S02', '双人间', '空', '否');
INSERT INTO `room` VALUES ('S03', '双人间', '空', '否');
INSERT INTO `room` VALUES ('S04', '双人间', '空', '否');
INSERT INTO `room` VALUES ('S05', '双人间', '空', '否');
INSERT INTO `room` VALUES ('T01', '特惠大床房', '空', '否');
INSERT INTO `room` VALUES ('T02', '特惠大床房', '空', '否');
INSERT INTO `room` VALUES ('T03', '特惠大床房', '空', '否');
INSERT INTO `room` VALUES ('T04', '特惠大床房', '空', '否');
INSERT INTO `room` VALUES ('T05', '特惠大床房', '空', '否');

-- ----------------------------
-- Table structure for room_type
-- ----------------------------
DROP TABLE IF EXISTS `room_type`;
CREATE TABLE `room_type` (
  `Rtype` varchar(20) NOT NULL,
  `Ramount` int(11) NOT NULL,
  `Rintro` varchar(20) NOT NULL,
  `Rprice` float(10,4) DEFAULT NULL,
  `Rrest` int(11) DEFAULT NULL,
  PRIMARY KEY (`Rtype`),
  KEY `Rtype` (`Rtype`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of room_type
-- ----------------------------
INSERT INTO `room_type` VALUES ('3D观影房', '3', '有早餐 25平方米 2人入住', '171.0000', '3');
INSERT INTO `room_type` VALUES ('单人间', '4', '无早餐 10-13平方米 1人入住', '100.0000', '4');
INSERT INTO `room_type` VALUES ('双人间', '5', '无早餐 25-30平方米 2人入住', '141.0000', '5');
INSERT INTO `room_type` VALUES ('特惠大床房', '5', '无早餐 15-17平方米 2人入住', '94.0000', '5');
INSERT INTO `room_type` VALUES ('精致大床房', '5', '无早餐 25-30平方米 2人入住', '122.0000', '5');
INSERT INTO `room_type` VALUES ('豪华大床房', '4', '有早餐 20平方米 2人入住', '159.0000', '4');

-- ----------------------------
-- Table structure for waiter
-- ----------------------------
DROP TABLE IF EXISTS `waiter`;
CREATE TABLE `waiter` (
  `Wid` varchar(20) NOT NULL,
  `Wpassword` varchar(20) NOT NULL,
  `Wrole` varchar(20) NOT NULL,
  `Wpriority` varchar(20) NOT NULL,
  `Wname` varchar(20) DEFAULT NULL,
  PRIMARY KEY (`Wid`),
  KEY `Wrole` (`Wrole`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of waiter
-- ----------------------------
INSERT INTO `waiter` VALUES ('test1', '12345', '前台服务员', '入住', '张三');
INSERT INTO `waiter` VALUES ('test2', '12345', '经理', '入住', '李四');
INSERT INTO `waiter` VALUES ('test3', '12345', '保洁员', '无权限', '王五');
INSERT INTO `waiter` VALUES ('test4', '12345', '收银员', '结账', '钱六');
