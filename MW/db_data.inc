<?php
/**
 * DB�ǡ������饹����
 *
 * SELECT�ˤ�äƵ��äƤ���DB�ǡ������갷���ޤ�
 * abstract���饹�ʤΤǡ�ɬ�����������Ƥ�������
 * 
 *
 * @package magicweapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  yyyy/mm/dd
 * @version $Id$
 **/

abstract class db_data {
//public:

  // �ǡ�����fetch��Ԥ�
  // false�ˤʤä���ǡ���̵��
  abstract public function fetch();

  // pos�ǥǡ����ΰ��֤����
  //virtual string get_data(const int pos) = 0;
  abstract public function get_data($pos);

  // ���߻��ꤵ��Ƥ룱�ԤΥǡ�������������
  //virtual vector<string> get_row(void) = 0;
  abstract public function get_row();
}
