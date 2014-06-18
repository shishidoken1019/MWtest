<?php
/***************************************************
 * Hello world Top Page
 *
 * @package
 * @access  public
 * @author
 * @create
 * @version
 ***************************************************/

require_once('base_model.inc');

class mw_index extends base_model {

public function execute() {

  
  $dbh = $this->get_db();
//	var_dump($dbh);
	
	// 入力されたと仮定するIDの設定
  $id = '10';
  //$id = "' or 1 = 1; --"; // テスト用

  // SELECT文の作成
  $sql = 'SELECT * FROM sales_receipt WHERE sales_receipt_id = :id ;';
	//var_dump($sql);
  // mw_sqlインスタンスを生成
  $mw_sql = new mw_sql();
  // XXX わざと順番を逆に。sql文の設定とbindは、どっちが先でもOKです。なので「動的にパラメタが変更する時」に楽な作りです。
  $mw_sql->bind(':id', $id, data_clump::DATATYPE_STRING);
  //
  $mw_sql->set_sql($sql);
  
  
    // 数値添字の配列として行を得る場合
  $res = $dbh->query($mw_sql);
  while($res->fetch()) {
    // 行全体を取得
    $row = $res->get_row();
var_dump($row);
    // 1つめのデータを取得
    $s = $res->get_data(0);
var_dump($s);
  }



  $conv = $this->get_conv();
  $conv->monoDic('message', 'Hello World!!!');
  
}

} // end of class