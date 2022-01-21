import MqbStatus from './StatusTab/MqbStatus'
import React, { FC } from 'react';
import { Navigate, Route, Routes } from 'react-router-dom';

import { Tab } from '@mui/material';

import { RouterTabs, useRouterTab, useLayoutTitle } from '../components';

import DemoInformation from './DemoInformation';
import LightStateRestForm from './LightStateRestForm';
import LightMqttSettingsForm from './LightMqttSettingsForm';
import LightStateWebSocketForm from './LightStateWebSocketForm';
import PqStatus from "./StatusTab/PqStatus";
import ShiftStatus from "./StatusTab/ShiftStatus";

const StatusTab: FC = () => {
  useLayoutTitle("Demo Project");
  const { routerTab } = useRouterTab();

  return (
    <>
      <RouterTabs value={routerTab}>
        <Tab value="mqb" label="Mqb Status" />
        <Tab value="pq" label="PQ Status" />
        <Tab value="shift" label="Shift Register Status" />

      </RouterTabs>
      <Routes>
        <Route path="mqb" element={<MqbStatus />} />
        <Route path="pq" element={<PqStatus />} />
        <Route path="shift" element={<ShiftStatus />} />
        <Route path="/*" element={<Navigate replace to="mqb" />} />
      </Routes>
    </>
  );
};

export default StatusTab;


