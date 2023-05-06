## 样式

[TOC]

### 公式位置

行内模式式使用`$...$`，在文本之间插入公式；显示模式`$$...$$`，在单独的一行使用。

### 上标、下标

上标： `^`，下标：`_`。
示例： `C_n^2` 为$C_n^2$。
前置上下标`{}_1^2\!C_3^4`为${}_1^2\!C_3^4$。

### 分组

把相同等级的表达式放到一起。
符号： `{}`
如`e^{10}`显示为$e^{10}$，而`e^10`则为$e^10$。

### 字体样式

| 显示                  | 符号                              | 字体                       |
| --------------------- | --------------------------------- | -------------------------- |
| $ABCabc$              | `$ABCabc$`                        | 直接写                     |
| $\text{ABCabc}$       | `\text{ABCabc}`                   | 文本格式（内部可以再使用`$ |
| $\mathbf{ABCabc}$     | `\mathbf{ABCabc}`                 | 加粗                       |
| $\boldsymbol{\alpha}$ | `\boldsymbol{\alpha}`             | 加粗（其它字符）           |
| $\mathit{ABCabc}$     | `\mathit{ABCabc}`                 | 斜体                       |
| $\pmb{ABCabc}$        | `\pmb{ABCabc}`                    | 粗斜体                     |
| $\mathbb{ABCabc}$     | `\mathbb{ABCabc}`或`\Bbb{ABCabc}` | blackboard bold font       |
| $\mathtt{ABCabc}$     | `\mathtt{ABCabc}`                 | typewriter font            |
| $\mathrm{ABCabc}$     | `\mathrm{ABCabc}`                 | roman font                 |
| $\mathsf{ABCabc}$     | `\mathsf{ABCabc}`                 | sans-serif font            |
| $\mathcal{ABCabc}$    | `\mathcal{ABCabc}`                | calligraphic letters       |
| $\mathscr{ABCabc}$    | `\mathscr{ABCabc}`                | script letters             |
| $\mathfrak{ABCabc}$   | `\mathfrak{ABCabc}`               | Frakur letters             |

### 字体大小

| 显示                 | 符号                 |
| -------------------- | -------------------- |
| $ABCabc$             | `ABCabc`             |
| $\tiny ABCabc$       | `\tiny ABCabc`       |
| $\small ABCabc$      | `\small ABCabc`      |
| $\normalsize ABCabc$ | `\normalsize ABCabc` |
| $\large ABCabc$      | `\large ABCabc`      |
| $\Large ABCabc$      | `\Large ABCabc`      |
| $\huge ABCabc$       | `\huge ABCabc`       |
| $\Huge ABCabc$       | `\Huge ABCabc`       |

使用分组的方式来控制不同字体的大小，如`ABC {\tiny ABC} {\large ABC}`显示为$ABC {\tiny ABC} {\large ABC}$。

## 希腊字母

| 小写       | 符号       | 大写       | 符号       | 小写       | 符号       | 大写       | 符号       |
| ---------- | ---------- | ---------- | ---------- | ---------- | ---------- | ---------- | ---------- |
| $\alpha$   | `\alpha`   | $\Alpha$   | `\Alpha`   | $\beta$    | `\beta`    | $\Beta$    | `\Beta`    |
| $\gamma$   | `\gamma`   | $\Gamma$   | `\Gamma`   | $\delta$   | `\delta`   | $\Delta$   | `\Delta`   |
| $\epsilon$ | `\epsilon` | $\Epsilon$ | `\Epsilon` | $\zeta$    | `\zeta`    | $\Zeta$    | `\Zeta`    |
| $\eta$     | `\eta`     | $\Eta$     | `\Eta`     | $\theta$   | `\theta`   | $\Theta$   | `\Theta`   |
| $\iota$    | `\iota`    | $\Iota$    | `\Iota`    | $\kappa$   | `\kappa`   | $\Kappa$   | `\Kappa`   |
| $\lambda$  | `\lambda`  | $\Lambda$  | `\Lambda`  | $\mu$      | `\mu`      | $\Mu$      | `\Mu`      |
| $\nu$      | `\nu`      | $\Nu$      | `\Nu`      | $\xi$      | `\xi`      | $\Xi$      | `\Xi`      |
| $\pi$      | `\pi`      | $\Pi$      | `\Pi`      | $\rho$     | `\rho`     | $\Rho$     | `\Rho`     |
| $\sigma$   | `\sigma`   | $\Sigma$   | `\Sigma`   | $\tau$     | `\tau`     | $\Tau$     | `\Tau`     |
| $\upsilon$ | `\upsilon` | $\Upsilon$ | `\Upsilon` | $\phi$     | `\phi`     | $\Phi$     | `\Phi`     |
| $\chi$     | `\chi`     | $\Chi$     | `\Chi`     | $\psi$     | `\psi`     | $\Psi$     | `\Psi`     |
| $omega$    | `omega`    | $\Omega$   | `\Omega`   | $\omicron$ | `\omicron` | $\Omicron$ | `\Omicron` |

若需要斜体希腊字母，加上前缀`var`。如`\varDelta`显示为$varDelta$。

## 算术运算

| 显示        | 符号          | 显示        | 符号          | 显示      | 符号      |
| ----------- | ------------- | ----------- | ------------- | --------- | --------- |
| $\times$    | `\times`      | $\div$      | `\div`        | $\cdot$   | `\cdot`   |
| $<$         | `<`           | $>$         | `>`           | $\ll$     | `\ll`     |
| $\gg$       | `\gg`         | $\lll$      | `\lll`        | $\pm$     | `\pm`     |
| $\le$       | `\le`或`\leq` | $\ge$       | `\ge`或`\geq` | $\mp$     | `\mp`     |
| $\leqq$     | `\leqq`       | $\geqq$     | `\geqq`       | $\neq$    | `\neq`    |
| $\leqslant$ | `\leqslant`   | $\geqslant$ | `\geqslant`   | $\approx$ | `\approx` |

## 集合

| 显示          | 符号          | 显示        | 符号        | 显示           | 符号           |
| ------------- | ------------- | ----------- | ----------- | -------------- | -------------- |
| $\supset$     | `\supset`     | $\supseteq$ | `\supseteq` | $\not \subset$ | `\not \subset` |
| $\complement$ | `\complement` | $\in$       | `\in`       | $\notin$       | `\notin`       |
| $\subset$     | `\subset`     | $\subseteq$ | `\subseteq` | $\subsetneq$   | `\subsetneq`   |
| $\cap$        | `\cap`        | $\cup$      | `\cup`      | $\varnothing$  | `\varnothing`  |
| $\emptyset$   | `\emptyset`   | $\setminus$ | `\setminus` |                |                |

## 逻辑运算

| 显示      | 符号              | 显示      | 符号           | 显示    | 符号            |
| --------- | ----------------- | --------- | -------------- | ------- | --------------- |
| $\land$   | `\land`或`\wedge` | $\lor$    | `\lor`或`\vee` | $\lnot$ | `\lnot`或`\neg` |
| $\forall$ | `\forall`         | $\exists$ | `\exists`      | $\top$  | `\top`          |
| $\vdash$  | `\vdash`          | $\vDash$  | `\vDash`       | $\bot$  | `\bot`          |

## 括号

| 括号                                               | 符号                                               |
| -------------------------------------------------- | :------------------------------------------------- |
| $(x)$                                              | `(x)`                                              |
| $\{ x \}$                                          | `\{ x \}`或`\lbrace x \rbrace`                     |
| $[x]$                                              | `[x]`                                              |
| $\vert x \vert$                                    | `\vert x \vert`                                    |
| $\Vert x \Vert$                                    | `\Vert x \Vert`                                    |
| $\langle x \rangle$                                | `\langle x \rangle`                                |
| $\lceil x \rceil$                                  | `\lceil x \rceil`                                  |
| $\lfloor x \rfloor$                                | `\lfloor x \rfloor`                                |
| $\left( \frac xy \right)$                          | `\left( \frac xy \right)`（让括号与公式相适应）    |
| $\left. \frac 12 \right\}$                         | `\left. \frac 12 \right\}`                         |
| $\left\{ \frac xy \middle. y \neq 0 \right\}$      | `\left\{ \frac xy \middle. y \neq 0 \right\}`      |
| $\Bigg(\bigg(\Big(\big((x) \big)\Big)\bigg)\Bigg)$ | `\Bigg(\bigg(\Big(\big((x) \big)\Big)\bigg)\Bigg)` |
| $\dbinom nr$                                       | `\dbinom nr`（二项式系数）                         |
| $\binom nr$                                        | `\binom nr`或者`{n \choose r}`                     |

## 空格

| 显示         | 命令         | 说明     |
| ------------ | ------------ | -------- |
| $a b$        | `a b`        | 无视空格 |
| $a \qquad b$ | `a \qquad b` |          |
| $a \quad b$  | `a \quad b`  |          |
| $a\ b$       | `a\ b`       |          |
| $a\;b$       | `a\;b`       |          |
| $a\,b$       | `a\,b`       |          |
| $a\!b$       | `a\!b`       |          |

## 求和、积分和微分

| 显示          | 符号          | 显示                    | 符号                    |
| ------------- | ------------- | ----------------------- | ----------------------- |
| $\sum_1^n$    | `\sum_1^n`    | $\sum_{i=0}^\infty x^2$ | `\sum_{i=0}^\infty x^2` |
| $\int$        | `\int`        | $\iint$                 | `\iint`                 |
| $\iiint$      | `\iiint`      | $\idotsint$             | `\idotsint`             |
| $\oint$       | `\oint`       | $\prod$                 | `\prod`                 |
| $\coprod$     | `\coprod`     | $\bigcap$               | `\bigcap`               |
| $\bigcup$     | `\bigcup`     | $\bigvee$               | `\bigvee`               |
| $\bigwedge$   | `\bigwedge`   | $\infty$                | `\infty`                |
| $\nabla$      | `\nabla`      | $\partial x$            | `\partial x`            |
| $\mathrm{d}x$ | `\mathrm{d}x` | $\dot x$                | `\dot x`                |
| $\ddot y$     | `\ddot y`     |                         |                         |

## 分式、根号和函数

| 显示                     | 符号                     | 说明                      |
| ------------------------ | ------------------------ | ------------------------- |
| $\frac 12$               | `\frac 12`               |                           |
| $\dfrac 12$              | `\dfrac 12`              | 强制分式为显示模式        |
| $\tfrac 12$              | `\tfrac 12`              | 强制分式为文本模式        |
| $\cfrac 12$              | `\cfrac 12`              | 用于连续分式              |
| $\frac {x^2}{1+x}$       | `\frac {x^2}{1+x}`       |                           |
| ${x^2 \over 1+x}$        | `{x^2 \over 1+x}`        | 用于复杂的分式            |
| $\sqrt{x^3}$             | `\sqrt{x^3}`             |                           |
| $\sqrt[3]{\frac xy}$     | `\sqrt[3]{\frac xy}`     |                           |
| $\sin x$                 | `\sin x`                 | 大部分可以使用`\`+ 函数名 |
| $\operatorname{arcsec}x$ | `\operatorname{arcsec}x` | 无标准函数名              |
| $\lim_{x \to 0}$         | `\lim_{x \to 0}`         |                           |
| $\varinjlim$             | `\varinjlim`             |                           |
| $\varprojlim$            | `\varprojlim`            |                           |
| $\varliminf$             | `\varliminf`             |                           |
| $\varlimsup$             | `\varlimsup`             |                           |

## 箭头符号

| 显示                     | 符号                          | 显示                   | 符号                     |
| ------------------------ | ----------------------------- | ---------------------- | ------------------------ |
| $\Rightarrow$            | `\Rightarrow`                 | $\Leftarrow$           | `\Leftarrow`             |
| $a \rightarrow b$        | `a \rightarrow b`             | $a \leftarrow b$       | `a \leftarrow b`         |
| $a \to b$                | `a \to b`（常用）             | $a \gets b$            | `a \gets b`（常用）      |
| $a \Longrightarrow b$    | `a \Longrightarrow b`         | $a \Longleftarrow b$   | `a \Longleftarrow b`     |
| $a \implies b$           | `a \implies b`（常用）        | $a \impliedby b$       | `a \impliedby b`（常用） |
| $\longrightarrow$        | `\longrightarrow`             | $\longleftarrow$       | `\longleftarrow`         |
| $\Leftrightarrow$        | `\Leftrightarrow`             | $\leftrightarrow$      | `\leftrightarrow`        |
| $\Longleftrightarrow$    | `\Longleftrightarrow`或`\iff` | $\longleftrightarrow$  | `\longleftrightarrow`    |
| $\xrightarrow[y>0]{x+y}$ | `\xrightarrow[y>0]{x+y}`      | $\xleftarrow{x+y}$     | `\xleftarrow{x+y}`       |
| $\longmapsto$            | `\longmapsto`                 | $\mapsto$              | `\mapsto`                |
| $\hookleftarrow$         | `\hookleftarrow`              | $\hookrightarrow$      | `\hookrightarrow`        |
| $\searrow$               | `\searrow`                    | $\nearrow$             | `\nearrow`               |
| $\nwarrow$               | `\nwarrow`                    | $\swarrow$             | `\swarrow`               |
| $\downarrow$             | `\downarrow`                  | $\uparrow$             | `\uparrow`               |
| $\upuparrows$            | `\upuparrows`                 | $\updownarrow$         | `\updownarrow`           |
| $\Uparrow$               | `\Uparrow`                    | $\downdownarrows$      | `\downdownarrows`        |
| $\Updownarrow$           | `\Updownarrow`                | $\Downarrow$           | `\Downarrow`             |
| $\rightharpoonup$        | `\rightharpoonup`             | $\leftharpoonup$       | `\leftharpoonup`         |
| $\rightharpoonup$        | `\rightharpoonup`             | $\leftharpoondown$     | `\leftharpoondown`       |
| $\upharpoonleft$         | `\upharpoonleft`              | $\downharpoonleft$     | `\downharpoonleft`       |
| $\upharpoonright$        | `\upharpoonright`             | $\downharpoonleft$     | `\downharpoonleft`       |
| $\rightleftharpoons$     | `\rightleftharpoons`          | $\leftrightharpoons$   | `\leftrightharpoons`     |
| $\rightrightarrows$      | `\rightrightarrows`           | $\leftleftarrows$      | `\leftleftarrows`        |
| $\Rrightarrow$           | `\Rrightarrow`                | $\Lleftarrow$          | `\Lleftarrow`            |
| $\rightleftarrows$       | `\rightleftarrows`            | $\rightleftarrows$     | `\rightleftarrows`       |
| $\nrightarrow$           | `\nrightarrow`                | $\nleftarrow$          | `\nleftarrow`            |
| $\nLeftarrow$            | `\nLeftarrow`                 | $\nRightarrow$         | `\nRightarrow`           |
| $\nleftrightarrow$       | `\nleftrightarrow`            | $\curvearrowleft$      | `\curvearrowleft`        |
| $\circlearrowleft$       | `\circlearrowleft`            | $\curvearrowright$     | `\curvearrowright`       |
| $\circlearrowright$      | `\circlearrowright`           | $\looparrowleft$       | `\looparrowleft`         |
| $\rightarrowtail$        | `\rightarrowtail`             | $\looparrowright$      | `\looparrowright`        |
| $\leftarrowtail$         | `\leftarrowtail`              | $\Lsh$                 | `\Lsh`                   |
| $\twoheadleftarrow$      | `\twoheadleftarrow`           | $\Rsh$                 | `\Rsh`                   |
| $\twoheadrightarrow$     | `\twoheadrightarrow`          | $\rightsquigarrow$     | `\rightsquigarrow`       |
|                          |                               | $\leftrightsquigarrow$ | `\leftrightsquigarrow`   |

## 几何和向量

| 显示                 | 符号                 | 显示                      | 符号                      |
| -------------------- | -------------------- | ------------------------- | ------------------------- |
| $\triangle$          | `\triangle`          | $\Diamond$                | `\Diamond`                |
| $\Box$               | `\Box`               | $\odot$                   | `\odot`                   |
| $\angle ABC$         | `\angle ABC`         | $30^\circ$                | `30^\circ`                |
| $\perp$              | `\perp`              | $\sim$                    | `\sim`                    |
| $\cong$              | `\cong`              | $\hat{a}$                 | `\hat{a}`                 |
| $\vec{a}$            | `\vec{a}`            | $\overrightarrow{AB}$     | `\overrightarrow{AB}`     |
| $\overleftarrow{AB}$ | `\overleftarrow{AB}` | $\overleftrightarrow{AB}$ | `\overleftrightarrow{AB}` |
| $\widehat{e f g}$    | `\widehat{e f g}`    |                           |                           |

## 音调

| 显示        | 符号        | 显示        | 符号        |
| ----------- | ----------- | ----------- | ----------- |
| $\bar a$    | `\bar a`    | $\acute{a}$ | `\acute{a}` |
| $\check{a}$ | `\check{a}` | $\grave{a}$ | `\grave{a}` |
| $\breve{a}$ | `\breve{a}` | $\dot{a}$   | `\dot{a}`   |
| $\ddot{a}$  | `\ddot{a}`  | $\dddot{a}$ | `\dddot{a}` |
| $\hat{a}$   | `\hat{a}`   | $\tilde{a}$ | `\tilde{a}` |

## 上、下划线和上、下括号

| 显示                             | 符号                             |
| -------------------------------- | -------------------------------- |
| $\overline{h i j}$               | `\overline{h i j}`               |
| $\underline{h i j}$              | `\underline{h i j}`              |
| $\underbrace{a+b+\cdots+z}_{10}$ | `\underbrace{a+b+\cdots+z}_{10}` |
| $\overbrace{a+b+\cdots+z}^{10}$  | `\overbrace{a+b+\cdots+z}^{10}`  |

## 特殊字符

| 符号            | 显示            | 符号             | 显示             | 符号           | 显示           |
| --------------- | --------------- | ---------------- | ---------------- | -------------- | -------------- |
| $\eth$          | `\eth`          | $\S$             | `\S`             | $\P$           | `\P`           |
| $\%$            | `\%`            | $\dagger$        | `\dagger`        | $\ddagger$     | `\ddagger`     |
| $\star$         | `\star`         | $\ast$           | `\ast`或`*`      | $\circ$        | `\circ`        |
| $\bullet$       | `\bullet`       | $\ldots$         | `\ldots`         | $\cdots$       | `\cdots`       |
| $\vdots$        | `\vdots`        | $\ddots$         | `\ddots`         | $\smile$       | `\smile`       |
| $\frown$        | `\frown`        | $\wr$            | `\wr`            | $\oplus$       | `\oplus`       |
| $\bigoplus$     | `\bigoplus`     | $\otimes$        | `\otimes`        | $\bigotimes$   | `\bigotimes`   |
| $\bigodot$      | `\bigodot`      | $\boxtimes$      | `\boxtimes`      | $\boxplus$     | `\boxplus`     |
| $\triangleleft$ | `\triangleleft` | $\triangleright$ | `\triangleright` | $\bot$         | `\bot`         |
| $\top$          | `\top`          | $\vdash$         | `\vdash`         | $\Vdash$       | `\Vdash`       |
| $\vDash$        | `\vDash`        | $\models$        | `\models`        | $\infty$       | `\infty`       |
| $\imath$        | `\imath`        | $\hbar$          | `\hbar`          | $\ell$         | `\ell`         |
| $\mho$          | `\mho`          | $\Finv$          | `\Finv`          | $\Re$          | `\Re`          |
| $\Im$           | `\Im`           | $\wp$            | `\wp`            | $\diamondsuit$ | `\diamondsuit` |
| $\heartsuit$    | `\heartsuit`    | $\clubsuit$      | `\clubsuit`      | $\spadesuit$   | `\spadesuit`   |
| $\Game$         | `\Game`         | $\flat$          | `\flat`          | $\natural$     | `\natural`     |
| $\sharp$        | `\sharp`        |                  |                  |                |                |

## 阵列

**语法：** `$$\begin{array}…\end{array}$$`，`r`右对齐，`l`左对齐，`c`居中，`|`垂直线，`\hline`横线，`\\`换行，元素之间以`&`间隔。

**示例：**

```txt
$$
  \begin{array}{c|lcr}
    n & \text{Left} & \text{Center} & \text{Right} \\
    \hline
    1 & 0.24 & 1 & 125 \\
    2 & -1 & 189 & -8 \\
    3 & -20 & 2000 & 1+10i
  \end{array}
$$
```

$$
\begin{array}{c|lcr}
    n & \text{Left} & \text{Center} & \text{Right} \\
    \hline
    1 & 0.24 & 1 & 125 \\
    2 & -1 & 189 & -8 \\
    3 & -20 & 2000 & 1+10i
  \end{array}
$$

## 矩阵

**语法：** `$$\begin{matrix}…\end{matrix}$$`，每行以`\\`结尾，元素之间以`&`间隔。

**示例：**

```text
$$
  \begin{matrix}
    1 & x & x^2 \\
    1 & y & y^2 \\
    1 & z & z^2 \\
  \end{matrix}
$$
```

$$
\begin{matrix}
    1 & x & x^2 \\
    1 & y & y^2 \\
    1 & z & z^2 \\
  \end{matrix}
$$

**添加括号：**

- `pmatrix`()()
- `bmatrix`[ ][ ]
- `Bmatrix`{ }{ }
- `vmatrix`| || |
- `Vmatrix`∥ ∥‖ ‖

**添加省略号：**

```text
$$
  \begin{pmatrix}
  	1 & a_1^2 & a_1^2 & \cdots & a_1^2 \\
 	 1 & a_2^2 & a_2^2 & \cdots & a_2^2 \\
  	\vdots & \vdots & \vdots & \ddots & \vdots \\
  	1 & a_n^2 & a_n^2 & \cdots & a_n^2 \\
  \end{pmatrix}
$$
```

$$
\begin{pmatrix}
  	1 & a_1^2 & a_1^2 & \cdots & a_1^2 \\
 	 1 & a_2^2 & a_2^2 & \cdots & a_2^2 \\
  	\vdots & \vdots & \vdots & \ddots & \vdots \\
  	1 & a_n^2 & a_n^2 & \cdots & a_n^2 \\
  \end{pmatrix}
$$

**水平增广矩阵：** 使用阵列语法，

```text
$$ 
  \left[
    \begin{array}{cc|c}
      1&2&3\\
      4&5&6
    \end{array}
  \right] 
$$
```

$$   \left[    \begin{array}{cc|c}      1&2&3\\      4&5&6    \end{array}  \right]  $$

**垂直增广矩阵：**

```text
$$
  \begin{pmatrix}
    a & b\\
    c & d\\
    \hline
    1 & 0\\
    0 & 1
  \end{pmatrix}
$$
```

$$
\begin{pmatrix}
    a & b\\
    c & d\\
    \hline
    1 & 0\\
    0 & 1
  \end{pmatrix}
$$

**在行内插入矩阵：**如$\big( \begin{smallmatrix} a & b \\ c & d \end{smallmatrix} \big)$的语法`$\big( \begin{smallmatrix} a & b \\ c & d \end{smallmatrix} \big)$`

## 等式对齐

**语法：** `\begin{align}…\end{align}`，每行以`\\`结尾，元素之间以`&`间隔。

**示例：**

```text
$$
  \begin{align}
    \sqrt{37} & = \sqrt{\frac{73^2-1}{12^2}} \tag{1}\\
     & = \sqrt{\frac{73^2}{12^2}\cdot\frac{73^2-1}{73^2}} \tag{2}\\ 
     & = \sqrt{\frac{73^2}{12^2}}\sqrt{\frac{73^2-1}{73^2}} \tag{3}\\
     & = \frac{73}{12}\sqrt{1 - \frac{1}{73^2}} \tag{4}\\ 
     & \approx \frac{73}{12}\left(1 - \frac{1}{2\cdot73^2}\right) \tag{5}
  \end{align}
$$
```

$$
\begin{align}
    \sqrt{37} & = \sqrt{\frac{73^2-1}{12^2}} \tag{1}\\
     & = \sqrt{\frac{73^2}{12^2}\cdot\frac{73^2-1}{73^2}} \tag{2}\\ 
     & = \sqrt{\frac{73^2}{12^2}}\sqrt{\frac{73^2-1}{73^2}} \tag{3}\\
     & = \frac{73}{12}\sqrt{1 - \frac{1}{73^2}} \tag{4}\\ 
     & \approx \frac{73}{12}\left(1 - \frac{1}{2\cdot73^2}\right) \tag{5}
  \end{align}
$$

## 分段函数

**语法：** `\begin{cases}…\end{cases}`，每行以`\\`结尾，元素之间以`&`间隔。

**示例：**

```text
$$
  f(n) =
    \begin{cases}
      n/2,  & \text{if $n$ is even} \\
      3n+1, & \text{if $n$ is odd}
    \end{cases}
$$
```

$$
f(n) =
    \begin{cases}
      n/2,  & \text{if $n$ is even} \\
      3n+1, & \text{if $n$ is odd}
    \end{cases}
$$

```text
$$  
  \left.
    \begin{array}{l}
    \text{if $n$ is even:}&n/2\\
    \text{if $n$ is odd:}&3n+1
    \end{array}
  \right\}
  =f(n)
$$
```

$$
\left.
    \begin{array}{l}
    \text{if $n$ is even:}&n/2\\
    \text{if $n$ is odd:}&3n+1
    \end{array}
  \right\}
  =f(n)
$$

## 编号

**语法：**`\tag`。

**示例：**

```text
$$ 
  y=x^2        \tag{1.5a}
$$
```

$$
y=x^2        \tag{1.5a}
$$