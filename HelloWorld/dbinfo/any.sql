-- MagicWeaponManual�p
-- SQL�ꎮ

-- �܂������R�[�h���w��
SET NAMES utf8;

-- ���V�[�g�e�[�u��
DROP TABLE IF EXISTS sales_receipt;
CREATE TABLE sales_receipt (
  `sales_receipt_id` varbinary(64) NOT NULL COMMENT '��ӂȃ��V�[�g�pID',
  `user_id` varbinary(64) NOT NULL COMMENT '���[�UID',
  `account_title_id` varbinary(64) NOT NULL COMMENT '�Ȗ�ID',
  `amount` int NOT NULL COMMENT '���z',
  `sales_receipt_date` date NOT NULL COMMENT '���V�[�g���t',
  PRIMARY KEY (`sales_receipt_id`)
)CHARACTER SET 'utf8', ENGINE=InnoDB, COMMENT='�P���R�[�h���P���V�[�g�ȃe�[�u��';