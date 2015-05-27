/*
This class is from Oracle PGX core demo and adjusted slightly.
*/
import static oracle.pgx.api.algorithms.Argument.createGraphArg;

import java.util.List;
import java.util.Map;

import java.io.File;
import oracle.pgx.api.*;
import oracle.pgx.api.algorithms.*;
import oracle.pgx.config.*;
import oracle.pgx.common.types.PropertyType;
import oracle.pgx.api.algorithms.Argument;
import oracle.pgx.api.admin.*;

public class pageRank {

  public static void main(String[] argv) throws Exception {

    if (argv.length != 4) {
      System.err.println("usage: " + pageRank.class.getName() + " <graph config path>"
                          + " <max error value:eg 0.001> " + "<damping factor: ususally 0.85>" 
                          + "<max number of iterations: eg 100>");
      System.exit(-1);
    }
    GraphConfig cfg = GraphConfigFactory.forAnyFormat().fromPath(argv[0]);

    String sessionId = null;
    Core core = null;
    try {
      core = Pgx.getCore();
      sessionId = core.createSession("my-session").get();
      LoadingResult graph = core.loadGraphWithProperties(sessionId, cfg).get();
      String graphName = graph.getGraphName();

      { // pagerank
        String rankName = core.createNodeProperty(sessionId, graphName, PropertyType.DOUBLE).get();
        String pagerank = BuiltinAlgorithms.Type.PGX_BUILTIN_K1_PAGERANK.getAnalysisName();
        Argument[] args = new Argument[] {
            //
            Argument.createGraphArg(graphName), //
            Argument.createDoubleInArg(Double.parseDouble(argv[1])), // max error value
            Argument.createDoubleInArg(Double.parseDouble(argv[2])), // damping factor
            Argument.createIntInArg(Integer.parseInt(argv[3])), // max no. of iterations
            Argument.createNodePropertyArg(rankName) //
        };
        InvocationResult<Void> ir = core.runAnalysis(sessionId, pagerank, args, Void.class).get();
        if (ir.isSuccess()) {
          System.out.println("pagerank computed in " + ir.getExecutionTimeMs() + " milliseconds");
        } else {
          ir.getException().printStackTrace();
        }

        // uncomment the following and adjust accordingly if you want to see the result
        // make sure the getNodePropertyValue is called on an existing node
        /*
        double value = (Double) core.getNodePropertyValue(sessionId, graphName, rankName, 1).get();
        System.out.println("getNodePropertyValue(1) = " + value);

        PropertyProxy<Double> rank = core.<Double>getNodePropertyProxy(sessionId, graphName, rankName).get();
        value = rank.getValueFor(1);
        System.out.println("rank.getValueFor(1) = " + value);
        Iterable<Map.Entry<Object, Double>> top3 = rank.getTopKValues(3);
        System.out.println("top3 = " + top3);
        Iterable<Map.Entry<Object, Double>> bottom3 = rank.getBottomKValues(3);
        System.out.println("bottom3 = " + bottom3);
        Iterable<Map.Entry<Object, Double>> allValues = rank.getValues();
        System.out.println("allValues = " + allValues);
        */
      }

    } finally {

      Control ctrl = Pgx.getControl();
      if (ctrl.isRunning()) {
        if (sessionId != null) {
          core.destroySession(sessionId).get();
        }
        ctrl.shutdownNow();
      }
    }
  }

}
