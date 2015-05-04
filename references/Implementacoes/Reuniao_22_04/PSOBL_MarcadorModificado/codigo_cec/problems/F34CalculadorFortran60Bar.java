/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package clonalg_metamodel.problems;

import clonalg_metamodel.base.ConstrainedProblem;
import clonalg_metamodel.base.Problem;
import clonalg_metamodel.util.Configuration;

/**
 *
 * @author hedersb
 */
public class F34CalculadorFortran60Bar extends Problem implements ConstrainedProblem {

    public static int primeiraVez = 1;
    protected int dimension;
    protected double[][] bound = null;
    private Configuration configuration;
    protected double[] boundBase = {0.5, 5};
    private double[] barra_60;
    private int mapeamento[];
    private double rho;

    public F34CalculadorFortran60Bar(Configuration configuration) {
	rho = 0.1;
	this.dimension = 25;
	this.configuration = configuration;
	barra_60 = new double[60];
	barra_60[          0] = 51.763809118452630;
	barra_60[          1] = 51.763808485303710;
	barra_60[          2] = 51.763809118452630;
	barra_60[          3] = 51.763809118452630;
	barra_60[          4] = 51.763808485303710;
	barra_60[          5] = 51.763809118452630;
	barra_60[          6] = 51.763809118452630;
	barra_60[          7] = 51.763808485303710;
	barra_60[          8] = 51.763809118452630;
	barra_60[          9] = 51.763809118452630;
	barra_60[         10] = 51.763808485303710;
	barra_60[         11] = 51.763809118452630;
	barra_60[         12] = 46.587427171331320;
	barra_60[         13] = 46.587433293627580;
	barra_60[         14] = 46.587427171331320;
	barra_60[         15] = 46.587427171331320;
	barra_60[         16] = 46.587433293627580;
	barra_60[         17] = 46.587427171331320;
	barra_60[         18] = 46.587427171331320;
	barra_60[         19] = 46.587433293627580;
	barra_60[         20] = 46.587427171331320;
	barra_60[         21] = 46.587427171331320;
	barra_60[         22] = 46.587433293627580;
	barra_60[         23] = 46.587427171331320;
	barra_60[         24] = 50.115292780189360;
	barra_60[         25] = 50.115296117011030;
	barra_60[         26] = 50.115294416491260;
	barra_60[         27] = 50.115292780189360;
	barra_60[         28] = 50.115296117011030;
	barra_60[         29] = 50.115294416491260;
	barra_60[         30] = 50.115292780189360;
	barra_60[         31] = 50.115296117011030;
	barra_60[         32] = 50.115294416491260;
	barra_60[         33] = 50.115292780189360;
	barra_60[         34] = 50.115296117011030;
	barra_60[         35] = 50.115294416491260;
	barra_60[         36] = 50.115294416491260;
	barra_60[         37] = 50.115296117011030;
	barra_60[         38] = 50.115292780189360;
	barra_60[         39] = 50.115294416491260;
	barra_60[         40] = 50.115296117011030;
	barra_60[         41] = 50.115292780189360;
	barra_60[         42] = 50.115294416491260;
	barra_60[         43] = 50.115296117011030;
	barra_60[         44] = 50.115292780189360;
	barra_60[         45] = 50.115294416491260;
	barra_60[         46] = 50.115296117011030;
	barra_60[         47] = 50.115292780189360;
	barra_60[         48] = 10.000000000000000;
	barra_60[         49] = 9.999996503124393;
	barra_60[         50] = 9.999996503124393;
	barra_60[         51] = 10.000000000000000;
	barra_60[         52] = 9.999996503124393;
	barra_60[         53] = 9.999996503124393;
	barra_60[         54] = 10.000000000000000;
	barra_60[         55] = 9.999996503124393;
	barra_60[         56] = 9.999996503124393;
	barra_60[         57] = 10.000000000000000;
	barra_60[         58] = 9.999996503124393;
	barra_60[         59] = 9.999996503124393;


//	matp(001:002)=01; matp(003:010)=02; matp(011:018)=03;
//	matp(019:034)=04; matp(035:046)=05; matp(047:058)=06;
//	matp(059:082)=07; matp(083:086)=08; matp(087:090)=09;
//	matp(091:098)=10; matp(099:106)=11; matp(107:122)=12;
//	matp(123:130)=13; matp(131:162)=14; matp(163:170)=15;
//	matp(171:186)=16; matp(187:194)=17; matp(195:226)=18;
//	matp(227:234)=19; matp(235:258)=20; matp(259:270)=21;
//	matp(271:318)=22; matp(319:330)=23; matp(331:338)=24;
//	matp(339:342)=25; matp(343:350)=26; matp(351:358)=27;
//	matp(359:366)=28; matp(367:382)=29; matp(383:390)=30;
//	matp(391:398)=31; matp(399:430)=32; matp(431:446)=33;
//	matp(447:462)=34; matp(463:486)=35; matp(487:498)=36;
//	matp(499:510)=37; matp(511:558)=38; matp(559:582)=39;
//	matp(583:606)=40; matp(607:630)=41; matp(631:642)=42;
//	matp(643:654)=43; matp(655:702)=44; matp(703:726)=45;
//	matp(727:750)=46; matp(751:774)=47; matp(775:786)=48;
//	matp(787:798)=49; matp(799:846)=50; matp(847:870)=51;
//	matp(871:894)=52; matp(895:902)=53; matp(903:906)=54;
//	matp(907:910)=55; matp(911:918)=56; matp(919:926)=57;
//	matp(927:934)=58; matp(935:60)=59;
	mapeamento = new int[60];
	//mapeamento dessa trelica eh diferente
	//barra indica qual agrupamento estah
	mapeamento[0] = 1;
	mapeamento[1] = 2;
	mapeamento[2] = 3;
	mapeamento[3] = 4;
	mapeamento[4] = 5;
	mapeamento[5] = 6;
	mapeamento[6] = 7;
	mapeamento[7] = 8;
	mapeamento[8] = 9;
	mapeamento[9] = 10;
	mapeamento[10] = 11;
	mapeamento[11] = 12;
	mapeamento[12] = 1;
	mapeamento[13] = 2;
	mapeamento[14] = 3;
	mapeamento[15] = 4;
	mapeamento[16] = 5;
	mapeamento[17] = 6;
	mapeamento[18] = 7;
	mapeamento[19] = 8;
	mapeamento[20] = 9;
	mapeamento[21] = 10;
	mapeamento[22] = 11;
	mapeamento[23] = 12;
	mapeamento[24] = 13;
	mapeamento[25] = 14;
	mapeamento[26] = 15;
	mapeamento[27] = 16;
	mapeamento[28] = 17;
	mapeamento[29] = 18;
	mapeamento[30] = 19;
	mapeamento[31] = 20;
	mapeamento[32] = 21;
	mapeamento[33] = 22;
	mapeamento[34] = 23;
	mapeamento[35] = 24;
	mapeamento[36] = 13;
	mapeamento[37] = 14;
	mapeamento[38] = 15;
	mapeamento[39] = 16;
	mapeamento[40] = 17;
	mapeamento[41] = 18;
	mapeamento[42] = 19;
	mapeamento[43] = 20;
	mapeamento[44] = 21;
	mapeamento[45] = 22;
	mapeamento[46] = 23;
	mapeamento[47] = 24;
	mapeamento[48] = 0;
	mapeamento[49] = 0;
	mapeamento[50] = 0;
	mapeamento[51] = 0;
	mapeamento[52] = 0;
	mapeamento[53] = 0;
	mapeamento[54] = 0;
	mapeamento[55] = 0;
	mapeamento[56] = 0;
	mapeamento[57] = 0;
	mapeamento[58] = 0;
	mapeamento[59] = 0;
    }

    public double evaluate(double[] gene) {
	double weight = 0;
	for (int i = 0; i < barra_60.length; i++) {
	    weight += barra_60[ i ] * gene[ mapeamento[i] ];
	}
	return weight * rho;
    }

    @Override
    protected double[] evaluateSolution(Object gene) {
	double[] x = null;
	if (gene instanceof double[]) {
	    x = (double[]) gene;
	} else {
	    int[] variableSize = new int[getNumberOfVariables()];
	    for (int i = 0; i < variableSize.length; i++) {
		variableSize[i] = configuration.getBinaryEncodingContinuousVariable();
	    }
	    x = configuration.getUtilitaries().getRealFromBinary((boolean[]) gene, variableSize, getBounds(), true, configuration.getBinaryEncodingContinuousVariable(), this);
	}
	//long t = System.currentTimeMillis();
	double restricoes[] = new double[198];
	double funcaoObjetiva = calcula60Bar(x, restricoes, primeiraVez);
	primeiraVez = 0;
	double retorno[] = new double[restricoes.length + 1];
	retorno[0] = funcaoObjetiva;
	for (int i = 0; i < restricoes.length; i++) {
	    retorno[i + 1] = restricoes[i];
	}
	//System.out.println("Tempo " + (System.currentTimeMillis()-t));
	return retorno;
    }

    @Override
    public double[][] getBounds() {
	if (bound == null) {
	    bound = new double[dimension][2];
	    for (int i = 0; i < bound.length; i++) {
		bound[i][0] = boundBase[0];
		bound[i][1] = boundBase[1];
	    }
	}
	return bound;
    }

    @Override
    public int getMaxNumberFitnessFuntionEvaluation() {
	return 12000;
	//return 35000;
    }

    @Override
    public double getBestValue() {
	throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public Problem clone() {
	return new F34CalculadorFortran60Bar(configuration);
    }

    private native double calcula60Bar(double[] x, double restricoes[], int flap);

    static {
	System.loadLibrary("Calcula60Bar");
    }
}
