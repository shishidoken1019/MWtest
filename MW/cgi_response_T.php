<?php

require_once('cgi_response.inc');

  # ���֥������Ⱥ���
  $ob = new cgi_response;

  # ������
  $ob->set_length(1023);
  //$ob->put();
  //$ob->is_need_convert();


  # �̾�ν�����
  $ob->set_content_html();
  $ob->put();
  $ob->is_need_convert();

/*

  # ������ʥ�åѡ�
  $ob->set_content_plain();
  $ob->is_need_convert();
  $ob->put();
  # ������
  $ob->set_content_jpeg();
  $ob->is_need_convert();
  $ob->put();
  $ob->set_content_gif();
  $ob->is_need_convert();
  $ob->put();
  $ob->set_content_png();
  $ob->is_need_convert();
  $ob->put();

  $ob->set_location("http://foo.com/"); # Location�إå���
  $ob->is_need_convert();
  $ob->put();

  $ob->set_status204(); # ���̤��Ѳ������ʤ�
  $ob->put();
  $ob->set_nocache(); # ���̥ǡ����򥭥�å��夷�ʤ�
  $ob->is_need_convert();
  $ob->put();

*/

?>
