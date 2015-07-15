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
public class F31CalculadorFortran72Bar extends Problem implements ConstrainedProblem {

    public static int primeiraVez = 1;
    private int dimension;
    private double[][] bound = null;
    private Configuration configuration;
    protected double[] boundBase = {0.1, 2.5};
    private double[] barra_72;
    private int mapeamento[];
    private double rho;

    public F31CalculadorFortran72Bar(Configuration configuration) {
	rho = 0.1;
	this.dimension = 16;
	this.configuration = configuration;
	barra_72 = new double[72];
	barra_72[           0] = 60.000000;     // comprimento da barra           1
	barra_72[           1] = 60.000000;     // comprimento da barra           2
	barra_72[           2] = 60.000000;     // comprimento da barra           3
	barra_72[           3] = 60.000000;     // comprimento da barra           4
	barra_72[           4] = 134.16408;     // comprimento da barra           5
	barra_72[           5] = 134.16408;     // comprimento da barra           6
	barra_72[           6] = 134.16408;     // comprimento da barra           7
	barra_72[           7] = 134.16408;     // comprimento da barra           8
	barra_72[           8] = 134.16408;     // comprimento da barra           9
	barra_72[           9] = 134.16408;     // comprimento da barra          10
	barra_72[          10] = 134.16408;     // comprimento da barra          11
	barra_72[          11] = 134.16408;     // comprimento da barra          12
	barra_72[          12] = 120.00000;     // comprimento da barra          13
	barra_72[          13] = 120.00000;     // comprimento da barra          14
	barra_72[          14] = 120.00000;     // comprimento da barra          15
	barra_72[          15] = 120.00000;     // comprimento da barra          16
	barra_72[          16] = 169.70563;     // comprimento da barra          17
	barra_72[          17] = 169.70563;     // comprimento da barra          18
	barra_72[          18] = 60.000000;     // comprimento da barra          19
	barra_72[          19] = 60.000000;     // comprimento da barra          20
	barra_72[          20] = 60.000000;     // comprimento da barra          21
	barra_72[          21] = 60.000000;     // comprimento da barra          22
	barra_72[          22] = 134.16408;     // comprimento da barra          23
	barra_72[          23] = 134.16408;     // comprimento da barra          24
	barra_72[          24] = 134.16408;     // comprimento da barra          25
	barra_72[          25] = 134.16408;     // comprimento da barra          26
	barra_72[          26] = 134.16408;     // comprimento da barra          27
	barra_72[          27] = 134.16408;     // comprimento da barra          28
	barra_72[          28] = 134.16408;     // comprimento da barra          29
	barra_72[          29] = 134.16408;     // comprimento da barra          30
	barra_72[          30] = 120.00000;     // comprimento da barra          31
	barra_72[          31] = 120.00000;     // comprimento da barra          32
	barra_72[          32] = 120.00000;     // comprimento da barra          33
	barra_72[          33] = 120.00000;     // comprimento da barra          34
	barra_72[          34] = 169.70563;     // comprimento da barra          35
	barra_72[          35] = 169.70563;     // comprimento da barra          36
	barra_72[          36] = 60.000000;     // comprimento da barra          37
	barra_72[          37] = 60.000000;     // comprimento da barra          38
	barra_72[          38] = 60.000000;     // comprimento da barra          39
	barra_72[          39] = 60.000000;     // comprimento da barra          40
	barra_72[          40] = 134.16408;     // comprimento da barra          41
	barra_72[          41] = 134.16408;     // comprimento da barra          42
	barra_72[          42] = 134.16408;     // comprimento da barra          43
	barra_72[          43] = 134.16408;     // comprimento da barra          44
	barra_72[          44] = 134.16408;     // comprimento da barra          45
	barra_72[          45] = 134.16408;     // comprimento da barra          46
	barra_72[          46] = 134.16408;     // comprimento da barra          47
	barra_72[          47] = 134.16408;     // comprimento da barra          48
	barra_72[          48] = 120.00000;     // comprimento da barra          49
	barra_72[          49] = 120.00000;     // comprimento da barra          50
	barra_72[          50] = 120.00000;     // comprimento da barra          51
	barra_72[          51] = 120.00000;     // comprimento da barra          52
	barra_72[          52] = 169.70563;     // comprimento da barra          53
	barra_72[          53] = 169.70563;     // comprimento da barra          54
	barra_72[          54] = 60.000000;     // comprimento da barra          55
	barra_72[          55] = 60.000000;     // comprimento da barra          56
	barra_72[          56] = 60.000000;     // comprimento da barra          57
	barra_72[          57] = 60.000000;     // comprimento da barra          58
	barra_72[          58] = 134.16408;     // comprimento da barra          59
	barra_72[          59] = 134.16408;     // comprimento da barra          60
	barra_72[          60] = 134.16408;     // comprimento da barra          61
	barra_72[          61] = 134.16408;     // comprimento da barra          62
	barra_72[          62] = 134.16408;     // comprimento da barra          63
	barra_72[          63] = 134.16408;     // comprimento da barra          64
	barra_72[          64] = 134.16408;     // comprimento da barra          65
	barra_72[          65] = 134.16408;     // comprimento da barra          66
	barra_72[          66] = 120.00000;     // comprimento da barra          67
	barra_72[          67] = 120.00000;     // comprimento da barra          68
	barra_72[          68] = 120.00000;     // comprimento da barra          69
	barra_72[          69] = 120.00000;     // comprimento da barra          70
	barra_72[          70] = 169.70563;     // comprimento da barra          71
	barra_72[          71] = 169.70563;     // comprimento da barra          72

	mapeamento = new int[17];
	mapeamento[0] = 0;
	mapeamento[1] = 4;
	mapeamento[2] = 12;
	mapeamento[3] = 16;
	mapeamento[4] = 18;
	mapeamento[5] = 22;
	mapeamento[6] = 30;
	mapeamento[7] = 34;
	mapeamento[8] = 36;
	mapeamento[9] = 40;
	mapeamento[10] = 48;
	mapeamento[11] = 52;
	mapeamento[12] = 54;
	mapeamento[13] = 58;
	mapeamento[14] = 66;
	mapeamento[15] = 70;
	mapeamento[16] = 72;
    }

    public double evaluate(double[] gene) {
	double weight = 0;
	int k = 0;
	int k1 = 1;
	for(int i = 0; i<barra_72.length; i++) {
	    if (mapeamento[k1] == i) {
		k++;
		k1++;
	    }
	    weight += barra_72[i] * gene[k] ;
	}
	return weight*rho;
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
	double restricoes[] = new double[168];
	double funcaoObjetiva = calcula72Bar(x, restricoes, primeiraVez);
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
	//return 1000000;
    }

    @Override
    public double getBestValue() {
	throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public Problem clone() {
	return new F31CalculadorFortran72Bar(configuration);
    }

    private native double calcula72Bar(double[] x, double restricoes[], int flap);

    static {
	System.loadLibrary("Calcula72Bar");
    }
}
