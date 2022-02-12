import MqbStatus from './StatusTab/MqbStatus'
import React, { FC } from 'react';
import { Navigate, Route, Routes } from 'react-router-dom';

import { Tab } from '@mui/material';

import { RouterTabs, useRouterTab, useLayoutTitle } from '../components';

import Debug from "./DebugTab/Debug";

const ConfigTab: FC = () => {
  useLayoutTitle("Demo Project");
  const { routerTab } = useRouterTab();

  return (
    <>
      <RouterTabs value={routerTab}>
        <Tab value="debug" label="Config" />
      </RouterTabs>
      <Routes>
        <Route path="debug" element={<Debug />} />
        <Route path="/*" element={<Navigate replace to="debug" />} />
      </Routes>
    </>
  );
};

export default ConfigTab;


