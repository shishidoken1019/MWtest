<?php

/**
 * XML <-> hash���� ����С���
 *
 * XML��hash����Ȥ�����Ѵ�����
 * XXX �Ȥꤢ�������ե�åȤʡ��ͥ��Ȥ����ĤΤ��б�
 * XXX in/out��EUC����ˤ�����äƤ롣Ŭ����ɬ�פʿͤ���������
 *
 * @package magicweapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  yyyy/mm/dd
 * @version $Id$
 **/

require_once('multimap.inc');
require_once('multibyte.inc');


//
class xml_hasharray_converter
{
//public:
public function __construct()
{
  //
  $this->init();
}

public function init()
{
  $this->data_ = new multimap;
  $this->document_element_name_ = "";
  $this->mobj_ = new multibyte;
  $this->mobj_->set_euc(); // XXX �Ȥꤢ����
  // �����������
  $this->inmobj_ = new multibyte;
  $this->inmobj_->set_utf8(); // XXX �Ȥꤢ����
}

//
public function set_document_element_name($s) { $this->document_element_name_ = $s; }
public function get_document_element_name() { return $this->document_element_name_; }

public function set_value($n, $v) { $this->data_->insert($n, $v); }
public function get_value($n) { return $this->data_->real($this->data_->find($n))->get_second(); }


// ��侩�᥽�å�
public function get_datas() { return $this->data_; }

//
public function make_xml()
{
$xml = "";

  $xml  = '<?xml version="1.0" encoding="UTF-8"?>' . "\n";
  $xml .= '<' . $this->get_document_element_name() . '>' . "\n";

  for($itr = $this->data_->begin(); $itr !== $this->data_->end(); $itr ++) {
//print $this->data_->real($itr)->get_first();
//print ' => ';
//print $this->data_->real($itr)->get_second();
//print "\n";
    $xml .= '  ' . '<' . $this->data_->real($itr)->get_first() . '>';
    $xml .= $this->inmobj_->convert($this->data_->real($itr)->get_second());
    $xml .= '</' . $this->data_->real($itr)->get_first() . '>';
    $xml .= "\n";
  }

  //
  $xml .= '</' . $this->get_document_element_name() . '>' . "\n";

  //
  return $xml;
}

//
public function set_xml($s) {
  // �Ȥꤢ��������򥯥ꥢ
  $this->data_ = new multimap;
  $this->document_element_name_ = "";

  //
  $xml = new SimpleXMLElement($s);

  // 
  $this->set_document_element_name($xml->getName());

  //
  $wk =  $xml->children();
//var_dump( $wk );
  foreach($wk as $key => $value) {
//print "$key -> $value \n";
    $this->set_value($key, $this->mobj_->convert($value));
  }
//print_r($this->data_);

}


//private:
private $data_;
private $document_element_name_;
private $mobj_; // multibyte ���󥹥���
private $inmobj_; // multibyte ���󥹥���

} // end of class
