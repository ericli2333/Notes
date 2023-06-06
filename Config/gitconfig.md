#! https://zhuanlan.zhihu.com/p/634709353
# 如何配置git
本文给出一种更改git配置文件快速配置git的方法，以及一些常用的配置。

## 配置文件
使用方法：
- 在~目录下新建.gitconfig文件（Windows下就是C:\Users\用户名，Linux下就是~）
- 在~目录下新建.gitignore文件
- 复制一下内容到对应文件中
- 
### .gitconfig文件内容
``` bash
[user]
	name = YOUR_NAME
	email = YOUR_EMAIL
[alias]
	co = commit
	st = status
	logl = log --graph --all --oneline
	ch = checkout
	cp = cherry-pick
[core]
	quotepath = false
	editor = code --wait --new-window
	excludesfile = ~/.gitignore
[filter "lfs"]
	process = git-lfs filter-process
	required = true
	clean = git-lfs clean -- %f
	smudge = git-lfs smudge -- %f
[diff]
	tool = vscode-diff
[difftool]
	prompt = false
[difftool "vscode-diff"]
	cmd = code --wait --diff $LOCAL $REMOTE
[merge]
	tool = vscode-merge
[mergetool "vscode-merge"]
	cmd = code --wait $MERGED
[init]
	defaultBranch = main
[http]
	sslVerify = false
[https]
	sslVerify = false
[branch]
	autosetuprebase = always
```

### .gitignore文件内容
```json
*.log
*.orig
*.exe
*.aux
*.fdb_latexmk
*.fls
*.out
*.toc
*.orig
## Core latex/pdflatex auxiliary files:
*.aux
*.lof
*.log
*.lot
*.fls
*.out
*.toc
*.fmt
*.fot
*.cb
*.cb2
.*.lb
.DS_Store
clean.bat
elegant*-cn.pdf
elegant*-en.pdf
*.dates

## Intermediate documents:
*.dvi
*.xdv
*-converted-to.*
# these rules might exclude image files for figures etc.
# *.ps
# *.eps
# *.pdf

## Generated if empty string is given at "Please type another file name for output:"
.pdf

## Bibliography auxiliary files (bibtex/biblatex/biber):
*.bbl
*.bcf
*.blg
*-blx.aux
*-blx.bib
*.run.xml

## Build tool auxiliary files:
*.fdb_latexmk
*.synctex
*.synctex(busy)
*.synctex.gz
*.synctex.gz(busy)
*.pdfsync

## Auxiliary and intermediate files from other packages:
# algorithms
*.alg
*.loa

# achemso
acs-*.bib

# amsthm
*.thm

# beamer
*.nav
*.pre
*.snm
*.vrb

# changes
*.soc

# cprotect
*.cpt

# elsarticle (documentclass of Elsevier journals)
*.spl

# endnotes
*.ent

# fixme
*.lox

# feynmf/feynmp
*.mf
*.mp
*.t[1-9]
*.t[1-9][0-9]
*.tfm

#(r)(e)ledmac/(r)(e)ledpar
*.end
*.?end
*.[1-9]
*.[1-9][0-9]
*.[1-9][0-9][0-9]
*.[1-9]R
*.[1-9][0-9]R
*.[1-9][0-9][0-9]R
*.eledsec[1-9]
*.eledsec[1-9]R
*.eledsec[1-9][0-9]
*.eledsec[1-9][0-9]R
*.eledsec[1-9][0-9][0-9]
*.eledsec[1-9][0-9][0-9]R

# glossaries
*.acn
*.acr
*.glg
*.glo
*.gls
*.glsdefs

# gnuplottex
*-gnuplottex-*

# gregoriotex
*.gaux
*.gtex

# htlatex
*.4ct
*.4tc
*.idv
*.lg
*.trc
*.xref

# hyperref
*.brf

# knitr
*-concordance.tex
# TODO Comment the next line if you want to keep your tikz graphics files
*.tikz
*-tikzDictionary

# listings
*.lol

# makeidx
*.idx
*.ilg
*.ind
*.ist

# minitoc
*.maf
*.mlf
*.mlt
*.mtc[0-9]*
*.slf[0-9]*
*.slt[0-9]*
*.stc[0-9]*

# minted
_minted*
*.pyg

# morewrites
*.mw

# nomencl
*.nlg
*.nlo
*.nls

# pax
*.pax

# pdfpcnotes
*.pdfpc

# sagetex
*.sagetex.sage
*.sagetex.py
*.sagetex.scmd

# scrwfile
*.wrt

# sympy
*.sout
*.sympy
sympy-plots-for-*.tex/

# pdfcomment
*.upa
*.upb

# pythontex
*.pytxcode
pythontex-files-*/

# thmtools
*.loe

# TikZ & PGF
*.dpth
*.md5
*.auxlock

# todonotes
*.tdo

# easy-todo
*.lod

# xmpincl
*.xmpi

# xindy
*.xdy

# xypic precompiled matrices
*.xyc

# endfloat
*.ttt
*.fff

# Latexian
TSWLatexianTemp*

## Editors:
# WinEdt
*.bak
*.sav

# Texpad
.texpadtmp

# Kile
*.backup

# KBibTeX
*~[0-9]*

# auto folder when using emacs and auctex
./auto/*

*.el

# expex forward references with \gathertags
*-tags.tex

# standalone packages
*.sta

# generated if using elsarticle.cls
*.spl
```