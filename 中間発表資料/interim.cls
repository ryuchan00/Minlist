%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 元は fsresume.sty (FS専攻合同輪講 TeXフォーマット)                 %
% 2017/06/30  変更した箇所にめっちゃ ! を入れといたかもしれない
%                                                               %
% 左右余白は3cm, ヘッダとフッタは小さい
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%jarticle.sty をインポート
\input{jarticle.sty}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%	タイトルを作成する。
%	日付の位置は
%		\dateposition{\flushright}
%	によって右詰めとなる(デフォルトはセンタリング)。
%     \@foo とかは変数
\newlength{\@titlespace}	% タイトルの縦長寸法
\setlength{\@titlespace}{5cm}	% デフォルト
\def\titlespace#1{\setlength{\@titlespace}{#1}}	% デフォルトの変更
\def\@dateposition{\flushright}  % 右余白に合わせたい !!!!!
\def\dateposition#1{\renewcommand{\@dateposition}{#1}}
%\def\origin#1{\def\@origin{#1}}
\def\thisevent#1{\def\@thisevent{#1}}  % 上のやつ !!!!!
\def\mymajor#1{\def\@mymajor{#1}}  % 専攻 !!!!!
\def\mynum#1{\def\@mynum{#1}}  % 学籍番号 !!!!!
\def\mylab#1{\def\@mylab{#1}}  % 研究室名 !!!!!
\def\myname#1{\def\@myname{#1}} % 氏名 !!!!!
\def\chukantitle{  % rinkou => chukantitle !!!!!
  \renewcommand\@maketitle{
    \newpage
    \twocolumn[
      \vbox to\@titlespace{
        \@dateposition{\@date} %  右余白に合わせたい !!!!!
        \begin{center}
        \@thisevent \\  \vskip .5em 
        {\Large \@title} \\  \vskip .5em 
        {\large \@mymajor \quad  % ここのスペースは調整する !!!!!!
                  学籍番号 : \@mynum \quad 
                  \@mylab \quad 
                  \@myname} \\
        \end{center}
      }
    ]
  }
}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 	２段組の各パラメータ値の設定。
%\twocolumn
\@twosidetrue
\@twocolumntrue
\sloppy
\flushbottom
\parindent 1em
%\oddsidemargin -4mm  % 奇数ページ左余白
%\evensidemargin -4mm  % 偶数数ページ左余白 !!!!!
\marginparwidth 10cm 
\marginparsep 10pt 
\textwidth 175mm
\linewidth 175mm
\textheight 265mm
\topmargin -2cm % 上の余白 描画領域とヘッダの間 !!!!! -2.3cm
\headheight 0pt
\footskip 10mm % 本文下端とフッタ下端 !!!!! 10mm
\hbadness=1000
\tolerance=5000 %(Must be less than 10000=sloppy in Japanese)
\setlength{\columnseprule}{.8pt}  % 真ん中の線 !!!!!!!!!!!!!!!!!!!!!!!!!!!

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% 余白3cmずつ !!!!!
%%% http://joker.hatenablog.com/entry/2012/07/09/153537 %%%
% 
%% ##################### Portrait Setting #########################
%% # TOP = 1inch + \voffset + \topmargin + \headheight + \headsep #
%% #     = 1inch + 0pt + 4pt + 20pt + 18pt (default)              #
%% # BOTTOM = \paperheight - TOP -\textheight                     #
%% ################################################################
%\setlength{\textheight}{\paperheight}   % 紙面縦幅を本文領域にする（BOTTOM=-TOP）
%\setlength{\topmargin}{4.6truemm}       % 上の余白を30mm（=1inch+4.6mm）に
%\addtolength{\topmargin}{-\headheight}  % 
%\addtolength{\topmargin}{-\headsep}     % ヘッダの分だけ本文領域を移動させる
%\addtolength{\textheight}{-60truemm}    % 下の余白も30mm（BOTTOM=-TOPだから+TOP+30mm）
% #################### Landscape Setting #######################
% # LEFT = 1inch + \hoffset + \oddsidemargin (\evensidemargin) #
% #      = 1inch + 0pt + 0pt                                   #
% # RIGHT = \paperwidth - LEFT - \textwidth                    #
% ##############################################################
\setlength{\textwidth}{\paperwidth}     % 紙面横幅を本文領域にする（RIGHT=-LEFT）
\setlength{\oddsidemargin}{-0.4truemm}  % 左の余白を25mm(=1inch-0.4mm)に
\setlength{\evensidemargin}{-0.4truemm} % 
\addtolength{\textwidth}{-50truemm}     % 右の余白も25mm（RIGHT=-LEFT）



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%	section の上下の空白
\renewcommand{\section}{\@startsection{section}{1}{\z@}%
   {.5\Cvs \@plus.3\Cvs}%
   {.5\Cvs \@plus.3\Cvs}%
   {\reset@font\Large\bfseries}}
\renewcommand{\subsection}{\@startsection{subsection}{2}{\z@}%
   {.5\Cvs \@plus.3\Cvs}%
   {.5\Cvs \@plus.3\Cvs}%
   {\reset@font\large\bfseries}}
\renewcommand{\subsubsection}{\@startsection{subsubsection}{3}{\z@}%
   {.5\Cvs \@plus.3\Cvs}%
   {.5\Cvs \@plus.3\Cvs}%
   {\reset@font\normalsize\bfseries}}
\renewcommand{\paragraph}{\@startsection{paragraph}{4}{\z@}%
   {-1em}%
   {-1em}%
   {\reset@font\normalsize\bfseries}}
\renewcommand{\subparagraph}{\@startsection{subparagraph}{5}{\z@}%
   {-1em}%
   {-1em}%
   {\reset@font\normalsize\bfseries}}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
