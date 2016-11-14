package org.fsm.fsmlib.runner

import groovy.json.JsonSlurper
import org.fsm.fsmlib.entity.TransitionRule
import org.fsm.fsmlib.machine.FSMConfig
import org.fsm.fsmlib.machine.FSMachine

/**
 * Created by vslepukhin on 18/09/2016.
 */
class FSMRunner {
    FSMConfig fsmConfig

    boolean quiet = false

    public FSMRunner(String configFile, boolean quiet = false) {
        def data = new JsonSlurper().parse(new File(configFile))
        this.fsmConfig = new FSMConfig(data)
        this.quiet = quiet
        if (!quiet)
            this.fsmConfig.describe()
    }

    public void run(String inputString) {
        println 'Must be implemented in FSM instance'
    }

    public  List tickMachine(List<FSMachine> currentMachineList, CharSequence aChar) {
        def newStates = []
        currentMachineList.each { FSMachine m -> newStates << m.feedChar(aChar, this.quiet) }
        return newStates.flatten().unique()
    }
}
