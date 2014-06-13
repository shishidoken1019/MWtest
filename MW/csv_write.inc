<?php

/**
 * CSV�񤭽Ф����饹
 *
 * ���åȤ��줿�ǡ�����CSVʸ����Ȥ��ƽ񤭽Ф���
 *
 * @package magicweapon
 * @access  public
 * @author  Kohei Yamada <hecomark@gmail.com>
 * @create  2007/07/28
 * @version $Id$
 **/

/*
// �Ȥ���

// CSV�Ȥ����Ǥ��Ф��ǡ����ϡ�(�Ȥꤢ����)���ԣ�����Ǻ��
$row1 = array("column1_1", "column1_2", "column1_3");
$row2 = array("column2_1", "column2_2", "column2_3");
$row3 = array("column3_1", "column3_2", "column3_3");

// write���󥹥��󥹺���
$writer = new csv_write;

// �ǡ�����push���Ƥ���
$writer->push_row($row1);
$writer->push_row($row2);
$writer->push_row($row3);

// ���ѥ졼���Ȳ���ʸ�����ѹ�������ϻ���
// �ǥե���ȤǤϡ����ѥ졼����,�ס�����ʸ����\r\n��
//$writer->set_separator("\t");
//$writer->set_crlf("\n");

// csv_str == CSV������ʸ����
$csv_str = $writer->get_string();

*/

require_once("csv_row.inc");

class csv_write
{
//public:

public function __construct() { $this->init(); }
public function init() {
	$this->rows_ = array();
	$this->sep_ = "";
	$this->crlf_ = "";

	// ���ڤ�ʸ���ϥ����
	// ���Ԥ�"\r\n"�ǽ����
	$this->set_separator(",");
	$this->set_crlf("\r\n");
}

/**
 * ����ʬ�Υǡ�����push����
 *
 * @param array $row
 * @return void
 * @access public
 */
public function push_row(array $row) {
	$csv_row = new csv_row;
	foreach ($row as $column) {
		$csv_row->push($column);
	}
	$this->rows_[] = $csv_row;
}

/**
 * �����Υ��ѥ졼���򥻥åȤ���
 *
 * @param string $sep
 * @return void
 * @access public
 */
public function set_separator($sep) {
	$this->sep_ = $sep;
}

/**
 * ���ԥ����ɤ���ꤹ��
 *
 * @param string $crlf
 * @return void
 * @access public
 */
public function set_crlf($crlf) {
	$this->crlf_ = $crlf;
}

/**
 * ���åȤ���Ƥ���ǡ�������CSVʸ�����������֤�
 *
 * @param void
 * @return string 
 * @access public
 */
public function get_string() {
	$str = "";
	foreach ($this->get_rows() as $row) {
		$row->set_separator($this->get_separator());
		$str .= $row->get_string() . $this->get_crlf();
	}
	return $str;
}

//protected:
protected function get_rows() { return $this->rows_; }
protected function get_separator() { return $this->sep_; }
protected function get_crlf() { return $this->crlf_; }

//private:

private $rows_;
private $sep_;
private $crlf_;


} // end_of_class



