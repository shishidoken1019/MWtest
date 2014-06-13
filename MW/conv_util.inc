<?php

require_once('secure_conv.inc');

// checked & selected ��
class conv_util
{

// checked�ѡ�radio , checkbox��
static public function monoDicChecked($conv, $name, $value)
{
  //
  if (is_array($value)) {
    $values = $value;
  } else {
    $values = array($value);
  }
  $conv->monoDicToku($name, "checked=\"checked\"", "", $values);
}

// selected�ѡ�select option ��
static public function monoDicSelected($conv, $name, $value)
{
  //
  if (is_array($value)) {
    $values = $value;
  } else {
    $values = array($value);
  }
//  $values = array($value);
  $conv->monoDicToku($name, "selected=\"selected\"", "", $values);
}

// simple_loop�ʤ������empty���б�
//conv_util::set_loop($conv, $data, 'ad_loop', "");
static public function set_loop($conv, $data, $name, $empty_name = "")
{
  // �ޤ�empty name�β��
  if ("" === $empty_name) {
    $empty_name = 'if_' . $name . '_empty';
  }
  // data�������loop���ʤ����emptyɽ��
  if (false === empty($data)) {
    $sl = new simple_loop;
    $sl->set_data($data);
    $conv->multiDic($name, $sl);
  } else {
    $sp = new simple_put;
    $conv->multiDic($empty_name, $sp);
  }
  
  //
  return ;
}


} // end of class

// ñ��ʥ롼��
class simple_loop
{
//public:

// �ǡ���copy
function set_data($d) {$this->data_ = $d; }

// 
public function secure_off() { $this->secure_flg_ = false; }

//
function  m_conv($body, $param) {
//print $body;exit;
//print "simple_loop start \n";
  $ret = "";
  // �֤��
  // XXX ���äݤ����ܤ���ΤǤȤꤢ������
  if (false === empty($this->data_)) {
    foreach ($this->data_ as $wk) {
      // ���Ф�
      if (true === $this->secure_flg_) {
        $c = new secure_conv;
      } else {
        $c = new f_conv;
      }
      foreach($wk as $key => $value) {
        if (is_bool($value)) {
          if (true === $value) {
            $sp = new simple_put;
            $c->multiDic($key, $sp);
          }
        } else 
        if (is_array($value)) {
//var_dump($value);
//var_dump($key);
          $sl = new simple_loop;
          $sl->set_data($value);
          $c->multiDic($key, $sl);
        } else {
//print "$key, $value \n";
          $c->monoDic($key, $value);
        }
      }
      // �ִ�
      $ret .= $c->conv($body);
    }
  }
  //
  return $ret;
}

//private:
private $data_;
private $secure_flg_ = true;
} // end of class

// ñ��ʽ���
class simple_put
{
//public:
function  m_conv($body, $param) {
  return $body;
}

} // end of class

// cgi_request����ΰ켰�����
class simple_request_put
{
//public:

//
public function set_request($o) { $this->req_ = $o; }
public function get_request() { return $this->req_; }

//
public function set_conv($o) { $this->conv_ = $o; }
public function get_conv() { return $this->conv_; }

// �ᥤ�����
public function set()
{
  //
  $c = $this->get_conv();
  $req = $this->get_request();

  // �ޤ�̾����켰���Ȥ���
  $allnames = $req->get_all_names();

  // XXX ���äݤ����ܤ���ΤǤȤꤢ������
  if (false === empty($allnames)) {
    foreach($allnames as $name) {
      // monoDic
      $c->monoDic($name, $req->find($name));

      // check_box��radio��name_c��
      //conv_util::monoDicChecked($c, $name . '_c', $req->find_array($name));
      conv_util::monoDicChecked($c, 'checked_' . $name, $req->find_array($name));

      // select��name_s��
      //conv_util::monoDicSelected($c, $name . '_s', $req->find_array($name));
      conv_util::monoDicSelected($c, 'selected_' . $name, $req->find_array($name));
    }
  }

  //
  return true;
}

//private:
private $req_;
private $conv_;
}

// ñ��ʥ롼��:conv���󥹥��󥹤���ꤹ�륿����
class simple_obj_loop
{
//public:

// �ǡ���copy
function set_data($d) {$this->data_ = $d; }

//
function  m_conv($body, $param) {
//print "simple_obj_loop start \n";
  $ret = "";
  // �֤��
  // XXX ���äݤ����ܤ���ΤǤȤꤢ������
  if (false === empty($this->data_)) {
    foreach ($this->data_ as $wk) {
      // ���Ф�
      // �ִ�
      $ret .= $wk->conv($body);
    }
  }
  //
  return $ret;
}

//private:
private $data_;
} // end of class

